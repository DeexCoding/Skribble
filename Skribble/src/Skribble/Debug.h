#pragma once

#include "Core.h"

#pragma warning(push, 0)

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#pragma warning(pop)

namespace Skribble
{
	class Debug
	{
	public:

		static void Initalize();

		static Ref<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return clientLogger; }

	private:

		static Ref<spdlog::logger> coreLogger;
		static Ref<spdlog::logger> clientLogger;
	};
}

//Core logs
#define SKRIBBLE_CORE_TRACE(...)   ::Skribble::Debug::GetCoreLogger()->trace(__VA_ARGS__)
#define SKRIBBLE_CORE_INFO(...)    ::Skribble::Debug::GetCoreLogger()->info(__VA_ARGS__)
#define SKRIBBLE_CORE_WARNING(...) ::Skribble::Debug::GetCoreLogger()->warn(__VA_ARGS__)
#define SKRIBBLE_CORE_ERROR(...)   ::Skribble::Debug::GetCoreLogger()->error(__VA_ARGS__)
#define SKRIBBLE_CORE_CRITICAL(...)   ::Skribble::Debug::GetCoreLogger()->critical(__VA_ARGS__)

//Client logs
#define SKRIBBLE_TRACE(...)        ::Skribble::Debug::GetClientLogger()->trace(__VA_ARGS__)
#define SKRIBBLE_INFO(...)         ::Skribble::Debug::GetClientLogger()->info(__VA_ARGS__)
#define SKRIBBLE_WARNING(...)      ::Skribble::Debug::GetClientLogger()->warn(__VA_ARGS__)
#define SKRIBBLE_ERROR(...)        ::Skribble::Debug::GetClientLogger()->error(__VA_ARGS__)
#define SKRIBBLE_CRITICAL(...)        ::Skribble::Debug::GetClientLogger()->critical(__VA_ARGS__)