#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Mayhem
{
	class MAYHEM_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return msCoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return msClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> msCoreLogger;
		static std::shared_ptr<spdlog::logger> msClientLogger;
	};
}

//Core log macros
#define MH_CORE_TRACE(...) ::Mayhem::Log::getCoreLogger()->trace(__VA_ARGS__)
#define MH_CORE_INFO(...)  ::Mayhem::Log::getCoreLogger()->info(__VA_ARGS__)
#define MH_CORE_WARN(...)  ::Mayhem::Log::getCoreLogger()->warn(__VA_ARGS__)
#define MH_CORE_ERROR(...) ::Mayhem::Log::getCoreLogger()->error(__VA_ARGS__)
#define MH_CORE_FATAL(...) ::Mayhem::Log::getCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define MH_TRACE(...) ::Mayhem::Log::getClientLogger()->trace(__VA_ARGS__)
#define MH_INFO(...)  ::Mayhem::Log::getClientLogger()->info(__VA_ARGS__)
#define MH_WARN(...)  ::Mayhem::Log::getClientLogger()->warn(__VA_ARGS__)
#define MH_ERROR(...) ::Mayhem::Log::getClientLogger()->error(__VA_ARGS__)
#define MH_FATAL(...) ::Mayhem::Log::getClientLogger()->fatal(__VA_ARGS__)