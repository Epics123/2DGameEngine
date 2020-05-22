#include "Log.h"

namespace Mayhem
{
	std::shared_ptr<spdlog::logger> Log::msCoreLogger;
	std::shared_ptr<spdlog::logger> Log::msClientLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		msCoreLogger = spdlog::stdout_color_mt("MAYHEM");
		msCoreLogger->set_level(spdlog::level::trace);

		msClientLogger = spdlog::stdout_color_mt("APP");
		msClientLogger->set_level(spdlog::level::trace);
	}
}