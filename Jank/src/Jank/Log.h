#pragma once

#include "Jank/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace Jank {
	class JANK_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define JANK_CORE_TRACE(...) ::Jank::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JANK_CORE_INFO(...)  ::Jank::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JANK_CORE_WARN(...)  ::Jank::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JANK_CORE_ERROR(...) ::Jank::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JANK_CORE_FATAL(...) ::Jank::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define JANK_TRACE(...) ::Jank::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JANK_INFO(...)  ::Jank::Log::GetClientLogger()->info(__VA_ARGS__)
#define JANK_WARN(...)  ::Jank::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JANK_ERROR(...) ::Jank::Log::GetClientLogger()->error(__VA_ARGS__)
#define JANK_FATAL(...) ::Jank::Log::GetClientLogger()->fatal(__VA_ARGS__)
