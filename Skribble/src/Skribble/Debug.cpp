#include "skpch.h"
#include "Debug.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Skribble
{
	Ref<spdlog::logger> Debug::coreLogger;
	Ref<spdlog::logger> Debug::clientLogger;

	void Debug::Initalize()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Skribble.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		coreLogger = CreateRef<spdlog::logger>("SKRIBBLE", begin(logSinks), end(logSinks));
		spdlog::register_logger(coreLogger);
		coreLogger->set_level(spdlog::level::trace);
		coreLogger->flush_on(spdlog::level::trace);

		clientLogger = CreateRef<spdlog::logger>("GAME", begin(logSinks), end(logSinks));
		spdlog::register_logger(clientLogger);
		clientLogger->set_level(spdlog::level::trace);
		clientLogger->flush_on(spdlog::level::trace);
	}
}