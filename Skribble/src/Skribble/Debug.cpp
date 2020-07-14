#include "Debug.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Skribble
{
	std::shared_ptr<spdlog::logger> Debug::coreLogger;
	std::shared_ptr<spdlog::logger> Debug::clientLogger;

	void Debug::Initalize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("SKRIBBLE");
		coreLogger->set_level(spdlog::level::trace);
		
		clientLogger = spdlog::stdout_color_mt("APP");
		clientLogger->set_level(spdlog::level::trace);
	}
}