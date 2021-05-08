#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define LOG_LEVEL_CRITICAL	spdlog::level::level_enum::critical
#define LOG_LEVEL_ERROR		spdlog::level::level_enum::err
#define LOG_LEVEL_WARN		spdlog::level::level_enum::warn
#define LOG_LEVEL_INFO		spdlog::level::level_enum::info
#define LOG_LEVEL_DEBUG		spdlog::level::level_enum::debug
#define LOG_LEVEL_TRACE		spdlog::level::level_enum::trace

#define DEFAULT_LOG_LEVEL LOG_LEVEL_DEBUG

#define __CHECK_CORE_NULL() \
	if (!Log::GetCoreLogger()) { \
		LOG_INIT(); \
		LOG_ERROR("Logger should be initialized explicitly! Make sure to use LOG_INIT()!"); \
	}
#define __CHECK_NULL() \
	if (!Log::GetClientLogger()) { \
		LOG_INIT(); \
		LOG_ERROR("Logger should be initialized explicitly! Make sure to use LOG_INIT()!"); \
	}


#ifdef _DEBUG
#define LOG_INIT(...)			Log::LogInit(__VA_ARGS__)
#define LOG_CORE_TRACE(...)		Log::LogCoreTrace(__VA_ARGS__)
#define LOG_CORE_DEBUG(...)		Log::LogCoreDebug(__VA_ARGS__)
#define LOG_CORE_INFO(...)		Log::LogCoreInfo(__VA_ARGS__)
#define LOG_CORE_WARN(...)		Log::LogCoreWarn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)		Log::LogCoreError(__VA_ARGS__)
#define LOG_CORE_CRITICAL(...)	Log::LogCoreCritical(__VA_ARGS__)
#define LOG_TRACE(...)			Log::LogTrace(__VA_ARGS__)
#define LOG_DEBUG(...)			Log::LogDebug(__VA_ARGS__)
#define LOG_INFO(...)			Log::LogInfo(__VA_ARGS__)
#define LOG_WARN(...)			Log::LogWarn(__VA_ARGS__)
#define LOG_ERROR(...)			Log::LogError(__VA_ARGS__)
#define LOG_CRITICAL(...)		Log::LogCritical(__VA_ARGS__)
#define LOG_SET_LOGLEVEL(...)	Log::SetLoglevel(__VA_ARGS__)
#else
#define LOG_INIT()				
#define LOG_CORE_TRACE(...)		
#define LOG_CORE_DEBUG(...)		
#define LOG_CORE_INFO(...)		
#define LOG_CORE_WARN(...)		
#define LOG_CORE_ERROR(...)		
#define LOG_CORE_CRITICAL(...)	
#define LOG_TRACE(...)	
#define LOG_DEBUG(...)	
#define LOG_INFO(...)	
#define LOG_WARN(...)	
#define LOG_ERROR(...)	
#define LOG_CRITICAL(...)
#define LOG_SET_LOGLEVEL(...)
#endif


class Log {
public:
	Log();
	~Log();

	static void Init(spdlog::level::level_enum level = DEFAULT_LOG_LEVEL);

	static void SetLogLevel(spdlog::level::level_enum level);

	inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; };
	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; };

	template <typename... T> static void LogInit(T... args)				{ Log::Init(args...); }
	template <typename... T> static void LogCoreTrace(T... args)		{ __CHECK_CORE_NULL(); Log::GetCoreLogger()->trace(args...); }
	template <typename... T> static void LogCoreDebug(T... args)		{ __CHECK_CORE_NULL(); Log::GetCoreLogger()->debug(args...); }
	template <typename... T> static void LogCoreInfo(T... args)			{ __CHECK_CORE_NULL(); Log::GetCoreLogger()->info(args...); }
	template <typename... T> static void LogCoreWarn(T... args)			{ __CHECK_CORE_NULL(); Log::GetCoreLogger()->warn(args...); }
	template <typename... T> static void LogCoreError(T... args)		{ __CHECK_CORE_NULL(); Log::GetCoreLogger()->error(args...); }
	template <typename... T> static void LogCoreCritical(T... args)		{ __CHECK_CORE_NULL(); Log::GetCoreLogger()->critical(args...); }
	template <typename... T> static void LogTrace(T... args)			{ __CHECK_NULL(); Log::GetClientLogger()->trace(args...); }
	template <typename... T> static void LogDebug(T... args)			{ __CHECK_NULL(); Log::GetClientLogger()->debug(args...); }
	template <typename... T> static void LogInfo(T... args)				{ __CHECK_NULL(); Log::GetClientLogger()->info(args...); }
	template <typename... T> static void LogWarn(T... args)				{ __CHECK_NULL(); Log::GetClientLogger()->warn(args...); }
	template <typename... T> static void LogError(T... args)			{ __CHECK_NULL(); Log::GetClientLogger()->error(args...); }
	template <typename... T> static void LogCritical(T... args)			{ __CHECK_NULL(); Log::GetClientLogger()->critical(args...); }

private:
	static std::shared_ptr<spdlog::logger> coreLogger;
	static std::shared_ptr<spdlog::logger> clientLogger;
};
