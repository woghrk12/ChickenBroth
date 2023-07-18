#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ChickenBroth
{
	class CHICKEN_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define CB_CORE_TRACE(...)		::ChickenBroth::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CB_CORE_INFO(...)		::ChickenBroth::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CB_CORE_WARN(...)		::ChickenBroth::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CB_CORE_ERROR(...)		::ChickenBroth::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CB_CORE_CRITICAL(...)	::ChickenBroth::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define CB_TRACE(...)			::ChickenBroth::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CB_INFO(...)			::ChickenBroth::Log::GetClientLogger()->info(__VA_ARGS__)
#define CB_WARN(...)			::ChickenBroth::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CB_ERROR(...)			::ChickenBroth::Log::GetClientLogger()->error(__VA_ARGS__)
#define CB_CRITICAL(...)		::ChickenBroth::Log::GetClientLogger()->critical(__VA_ARGS__)