#pragma once

#ifndef SPDLOG
#define SPDLOG

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define LOG_LEVEL_CRITICAL	spdlog::level::level_enum::critical
#define LOG_LEVEL_ERROR		spdlog::level::level_enum::err
#define LOG_LEVEL_WARN		spdlog::level::level_enum::warn
#define LOG_LEVEL_INFO		spdlog::level::level_enum::info
#define LOG_LEVEL_DEBUG		spdlog::level::level_enum::debug
#define LOG_LEVEL_TRACE		spdlog::level::level_enum::trace

#define DEFAULT_LOG_LEVEL LOG_LEVEL_DEBUG

namespace Robotino {
	namespace Log {

		extern std::shared_ptr<spdlog::logger> coreLogger;
		extern std::shared_ptr<spdlog::logger> clientLogger;

	}
}

#ifdef DEBUG

#define LOG_SET_BATTERY_LOGLEVEL(...)	Robotino::Log::coreLogger->set_level(__VA_ARGS__)
#define LOG_SET_CLIENT_LOGLEVEL(...)	Robotino::Log::clientLogger->set_level(__VA_ARGS__)
#define LOG_SET_LOGLEVEL(...)			{ LOG_SET_BATTERY_LOGLEVEL(__VA_ARGS__); LOG_SET_CLIENT_LOGLEVEL(__VA_ARGS__); }

#define ROBOTINOLIB_INIT_LOGGER()		{	if (!Robotino::Log::coreLogger || !Robotino::Log::clientLogger) {	\
												spdlog::set_pattern("%^[%T] %n: %v%$"); \
												Robotino::Log::coreLogger = spdlog::stdout_color_mt("RobotinoLib"); \
												Robotino::Log::clientLogger = spdlog::stdout_color_mt("Application"); \
												LOG_SET_LOGLEVEL(DEFAULT_LOG_LEVEL); \
											} \
										}

#define LOG_CORE_TRACE(...)				{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::coreLogger->trace(__VA_ARGS__);				}
#define LOG_CORE_WARN(...)				{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::coreLogger->warn(__VA_ARGS__);				}
#define LOG_CORE_DEBUG(...)				{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::coreLogger->debug(__VA_ARGS__);				}
#define LOG_CORE_INFO(...)				{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::coreLogger->info(__VA_ARGS__);				}
#define LOG_CORE_ERROR(...)				{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::coreLogger->error(__VA_ARGS__);				}
#define LOG_CORE_CRITICAL(...)			{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::coreLogger->critical(__VA_ARGS__);			}
#define LOG_TRACE(...)					{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::clientLogger->trace(__VA_ARGS__);			}
#define LOG_WARN(...)					{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::clientLogger->warn(__VA_ARGS__);			}
#define LOG_DEBUG(...)					{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::clientLogger->debug(__VA_ARGS__);			}
#define LOG_INFO(...)					{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::clientLogger->info(__VA_ARGS__);			}
#define LOG_ERROR(...)					{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::clientLogger->error(__VA_ARGS__);			}
#define LOG_CRITICAL(...)				{ ROBOTINOLIB_INIT_LOGGER(); Robotino::Log::clientLogger->critical(__VA_ARGS__);		}

#else

#define LOG_SET_BATTERY_LOGLEVEL(...)	{ ; }
#define LOG_SET_CLIENT_LOGLEVEL(...)	{ ; }
#define LOG_SET_LOGLEVEL(...)			{ ; }

#define LOG_CORE_TRACE(...)				{ ; }
#define LOG_CORE_WARN(...)				{ ; }
#define LOG_CORE_DEBUG(...)				{ ; }
#define LOG_CORE_INFO(...)				{ ; }
#define LOG_CORE_ERROR(...)				{ ; }
#define LOG_CORE_CRITICAL(...)			{ ; }
#define LOG_TRACE(...)					{ ; }
#define LOG_WARN(...)					{ ; }
#define LOG_DEBUG(...)					{ ; }
#define LOG_INFO(...)					{ ; }
#define LOG_ERROR(...)					{ ; }
#define LOG_CRITICAL(...)				{ ; }

#endif

#endif // SPDLOG
