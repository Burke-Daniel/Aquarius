#include "Log.h"

INITIALIZE_EASYLOGGINGPP

namespace Aquarius {

	el::Logger* Log::s_clientLogger;
	el::Logger* Log::s_coreLogger;

	void Log::initLoggers()
	{
		el::Configurations coreConfig;
		el::Configurations clientConfig;
		
		el::Loggers::addFlag(el::LoggingFlag::MultiLoggerSupport);

		coreConfig.set(el::Level::Global, el::ConfigurationType::Format, "AQ_CORE %level [%datetime] - %msg");
		coreConfig.set(el::Level::Global, el::ConfigurationType::Enabled, "true");
		
		clientConfig.set(el::Level::Global, el::ConfigurationType::Format, "%level [%datetime] - %msg");
		clientConfig.set(el::Level::Global, el::ConfigurationType::Enabled, "true");

		s_coreLogger = el::Loggers::getLogger("Core");
		s_clientLogger = el::Loggers::getLogger("Client");

		el::Loggers::reconfigureLogger("Core", coreConfig);
		el::Loggers::reconfigureLogger("Client", clientConfig);
	}
} // namespace Aquarius
