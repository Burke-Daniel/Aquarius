#pragma once

#include "easylogging++.h"

// Note: for printf-like formatting, use only %v instead of type specific identifiers within log string

// Core log macros
#define AQ_CORE_TRACE(String, ...)      ::Aquarius::Log::getCoreLogger()->trace(String, ##__VA_ARGS__)
#define AQ_CORE_INFO(String, ...)       ::Aquarius::Log::getCoreLogger()->info(String, ##__VA_ARGS__)
#define AQ_CORE_WARNING(String, ...)    ::Aquarius::Log::getCoreLogger()->warn(String, ##__VA_ARGS__)
#define AQ_CORE_ERROR(String, ...)      ::Aquarius::Log::getCoreLogger()->error(String, ##__VA_ARGS__)
#define AQ_CORE_FATAL(String, ...)      ::Aquarius::Log::getCoreLogger()->fatal(String, ##__VA_ARGS__)

// Client log macros
#define AQ_TRACE(String, ...)           ::Aquarius::Log::getClientLogger()->trace(String, ##__VA_ARGS__)
#define AQ_INFO(String, ...)            ::Aquarius::Log::getClientLogger()->info(String, ##__VA_ARGS__)
#define AQ_WARNING(String, ...)         ::Aquarius::Log::getClientLogger()->warn(String, ##__VA_ARGS__)
#define AQ_ERROR(String, ...)           ::Aquarius::Log::getClientLogger()->error(String, ##__VA_ARGS__)
#define AQ_FATAL(String, ...)           ::Aquarius::Log::getClientLogger()->fatal(String, ##__VA_ARGS__)


namespace Aquarius {

	class Log
	{
	public:
		static void initLoggers();

		static el::Logger* getClientLogger() { return s_clientLogger; }
		static el::Logger* getCoreLogger() { return s_coreLogger; }
	private:
		Log() = delete;

		static el::Logger* s_clientLogger;
		static el::Logger* s_coreLogger;
	};
} // namespace Aquarius
