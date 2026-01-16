#pragma once


#include "Core.h"
#include "spdlog/spdlog.h"
#include"spdlog/fmt/ostr.h"

namespace YSJEN {

	class YSJEN_API Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

//core log macros
#define YE_CORE_TRACE(...) ::YSJEN::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define YE_CORE_INFO(...)  ::YSJEN::Log::GetCoreLogger()->info(__VA_ARGS__)
#define YE_CORE_WARN(...)  ::YSJEN::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define YE_CORE_ERROR(...) ::YSJEN::Log::GetCoreLogger()->error(__VA_ARGS__)
#define YE_CORE_FATAL(...) ::YSJEN::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//core log macros
#define YE_TRACE(...) ::YSJEN::Log::GetClientLogger()->trace(__VA_ARGS__)
#define YE_INFO(...)  ::YSJEN::Log::GetClientLogger()->info(__VA_ARGS__)
#define YE_WARN(...)  ::YSJEN::Log::GetClientLogger()->warn(__VA_ARGS__)
#define YE_ERROR(...) ::YSJEN::Log::GetClientLogger()->error(__VA_ARGS__)
#define YE_FATAL(...) ::YSJEN::Log::GetClientLogger()->fatal(__VA_ARGS__)


