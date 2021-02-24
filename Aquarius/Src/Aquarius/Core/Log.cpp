#include "Log.h"

INITIALIZE_EASYLOGGINGPP

namespace Aquarius {

	el::Logger* Log::s_clientLogger;
	el::Logger* Log::s_coreLogger;

	el::Configurations Log::s_clientConfig;
	el::Configurations Log::s_coreConfig;

	void Log::initLoggers()
	{
		el::Loggers::addFlag(el::LoggingFlag::MultiLoggerSupport);

		s_coreConfig.set(el::Level::Global, el::ConfigurationType::Format, "AQ_CORE %level [%datetime] - %msg");
		s_coreConfig.set(el::Level::Global, el::ConfigurationType::ToFile, "false");
		s_coreConfig.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
		s_coreConfig.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
		s_coreConfig.set(el::Level::Verbose, el::ConfigurationType::Enabled, "false");
		
		s_clientConfig.set(el::Level::Global, el::ConfigurationType::Format, "%level [%datetime] - %msg");
		s_clientConfig.set(el::Level::Global, el::ConfigurationType::ToFile, "false");
		s_clientConfig.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
		s_clientConfig.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
		s_clientConfig.set(el::Level::Verbose, el::ConfigurationType::Enabled, "false");

		s_coreLogger = el::Loggers::getLogger("Core");
		s_clientLogger = el::Loggers::getLogger("Client");

		el::Loggers::reconfigureLogger("Core", s_coreConfig);
		el::Loggers::reconfigureLogger("Client", s_clientConfig);
	}

	void Log::setClientLogFile(const std::string& fileName)
	{
		s_clientConfig.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
		s_clientConfig.set(el::Level::Global, el::ConfigurationType::Filename, fileName);
		el::Loggers::reconfigureLogger("Client", s_clientConfig);
	}

	void Log::setCoreLogFile(const std::string& fileName)
	{
		s_coreConfig.set(el::Level::Global, el::ConfigurationType::ToFile, "true");
		s_coreConfig.set(el::Level::Global, el::ConfigurationType::Filename, fileName);
		el::Loggers::reconfigureLogger("Core", s_coreConfig);
	}

	void Log::setLogLevel(LogLevel newLevel)
	{
		s_coreConfig.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
		s_clientConfig.set(el::Level::Global, el::ConfigurationType::Enabled, "true");

		// We don't use these levels so they are always disabled
		s_coreConfig.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
		s_coreConfig.set(el::Level::Verbose, el::ConfigurationType::Enabled, "false");
		s_clientConfig.set(el::Level::Debug, el::ConfigurationType::Enabled, "false");
		s_clientConfig.set(el::Level::Verbose, el::ConfigurationType::Enabled, "false");

		if (newLevel > LogLevel::Trace)
		{
			s_coreConfig.set(el::Level::Trace, el::ConfigurationType::Enabled, "false");
			s_clientConfig.set(el::Level::Trace, el::ConfigurationType::Enabled, "false");
		}

		if (newLevel > LogLevel::Info)
		{
			s_coreConfig.set(el::Level::Info, el::ConfigurationType::Enabled, "false");
			s_clientConfig.set(el::Level::Info, el::ConfigurationType::Enabled, "false");
		}

		if (newLevel > LogLevel::Warning)
		{
			s_coreConfig.set(el::Level::Warning, el::ConfigurationType::Enabled, "false");
			s_clientConfig.set(el::Level::Warning, el::ConfigurationType::Enabled, "false");
		}

		if (newLevel > LogLevel::Error)
		{
			s_coreConfig.set(el::Level::Error, el::ConfigurationType::Enabled, "false");
			s_clientConfig.set(el::Level::Error, el::ConfigurationType::Enabled, "false");
		}

		if (newLevel > LogLevel::Fatal)
		{
			s_coreConfig.set(el::Level::Fatal, el::ConfigurationType::Enabled, "false");
			s_clientConfig.set(el::Level::Fatal, el::ConfigurationType::Enabled, "false");
		}

		el::Loggers::reconfigureLogger("Client", s_clientConfig);
		el::Loggers::reconfigureLogger("Core", s_coreConfig);
	}

} // namespace Aquarius
