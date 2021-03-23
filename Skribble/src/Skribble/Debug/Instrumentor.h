#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

#include "Skribble/Core/Debug.h"

namespace Skribble
{

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	public:
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(mutex);

			if (currentSession)
			{
				if (Debug::GetCoreLogger())
				{
					SKRIBBLE_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", 
						name, currentSession->Name);
				}

				InternalEndSession();
			}

			outputStream.open(filepath);

			if (outputStream.is_open())
			{
				currentSession = new InstrumentationSession({ name });
				WriteHeader();
			}
			else
			{
				if (Debug::GetCoreLogger())
				{
					SKRIBBLE_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
		}

		void EndSession()
		{
			std::lock_guard lock(mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(mutex);

			if (currentSession)
			{
				outputStream << json.str();
				outputStream.flush();
			}
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	private:
		Instrumentor()
			: currentSession(nullptr)
		{
		}

		~Instrumentor()
		{
			EndSession();
		}

		void WriteHeader()
		{
			outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			outputStream.flush();
		}

		void WriteFooter()
		{
			outputStream << "]}";
			outputStream.flush();
		}

		void InternalEndSession()
		{
			if (currentSession)
			{
				WriteFooter();
				outputStream.close();
				delete currentSession;
				currentSession = nullptr;
			}
		}
	private:
		std::mutex mutex;
		InstrumentationSession* currentSession;
		std::ofstream outputStream;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: name(name), stopped(false)
		{
			startTimepoint = std::chrono::steady_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ startTimepoint.time_since_epoch() };
			auto elapsedTime = 
				std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - 
				std::chrono::time_point_cast<std::chrono::microseconds>(startTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ name, highResStart, elapsedTime, std::this_thread::get_id() });

			stopped = true;
		}
	private:
		const char* name;
		std::chrono::time_point<std::chrono::steady_clock> startTimepoint;
		bool stopped;
	};

	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;

			while (srcIndex < N)
			{
				size_t matchIndex = 0;

				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && 
					expr[srcIndex + matchIndex] == remove[matchIndex])
				{
					matchIndex++;
				}

				if (matchIndex == K - 1)
				{
					srcIndex += matchIndex;
				}

				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];

				srcIndex++;
			}

			return result;
		}
	}
}

#define SKRIBBLE_PROFILE 0

#if SKRIBBLE_PROFILE
#define SKRIBBLE_PROFILE_BEGIN_SESSION(name, filepath) ::Skribble::Instrumentor::Get().BeginSession(name, filepath)
#define SKRIBBLE_PROFILE_END_SESSION() ::Skribble::Instrumentor::Get().EndSession()
#define SKRIBBLE_PROFILE_SCOPE(name) ::Skribble::InstrumentationTimer timer##__LINE__(name);
#else
#define SKRIBBLE_PROFILE_BEGIN_SESSION(name, filepath)
#define SKRIBBLE_PROFILE_END_SESSION()
#define SKRIBBLE_PROFILE_SCOPE(name)
#endif