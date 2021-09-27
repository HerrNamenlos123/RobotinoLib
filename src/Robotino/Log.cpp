
#include "Robotino/Log.h"

std::shared_ptr<spdlog::logger> Log::coreLogger;
std::shared_ptr<spdlog::logger> Log::clientLogger;

Log::Log() {

}

Log::~Log() {

}

void Log::Init(spdlog::level::level_enum level) {
	spdlog::set_pattern("%^[%T] %n: %v%$");

	coreLogger = spdlog::stdout_color_mt("RobotinoLib");
	clientLogger = spdlog::stdout_color_mt("Application");

	SetLogLevel(level);
}

void Log::SetLogLevel(spdlog::level::level_enum level) {
	__CHECK_CORE_NULL();
	__CHECK_NULL();

	coreLogger->set_level(level);
	clientLogger->set_level(level);
}
