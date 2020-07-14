#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Skribble
{
	class SKRIBBLE_API Debug
	{
	public:
		static void Initalize();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }

	private:
	 	static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

//Core logs
#define SKRIBBLE_CORE_TRACE(...)   ::Skribble::Debug::GetCoreLogger()->trace(__VA_ARGS__)
#define SKRIBBLE_CORE_INFO(...)    ::Skribble::Debug::GetCoreLogger()->info(__VA_ARGS__)
#define SKRIBBLE_CORE_WARNING(...) ::Skribble::Debug::GetCoreLogger()->warn(__VA_ARGS__)
#define SKRIBBLE_CORE_ERROR(...)   ::Skribble::Debug::GetCoreLogger()->error(__VA_ARGS__)
#define SKRIBBLE_CORE_FATAL(...)   ::Skribble::Debug::GetCoreLogger()->fatal(__VA_ARGS__)

//Client logs
#define SKRIBBLE_TRACE(...)        ::Skribble::Debug::GetClientLogger()->trace(__VA_ARGS__)
#define SKRIBBLE_INFO(...)         ::Skribble::Debug::GetClientLogger()->info(__VA_ARGS__)
#define SKRIBBLE_WARNING(...)      ::Skribble::Debug::GetClientLogger()->warn(__VA_ARGS__)
#define SKRIBBLE_ERROR(...)        ::Skribble::Debug::GetClientLogger()->error(__VA_ARGS__)
#define SKRIBBLE_FATAL(...)        ::Skribble::Debug::GetClientLogger()->fatal(__VA_ARGS__)