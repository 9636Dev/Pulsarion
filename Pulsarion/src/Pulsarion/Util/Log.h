#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>

namespace Pulsarion {

    // Used for internal use, not exported
    class Log
    {
    public:
        static void Init();

        [[nodiscard]] inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_CoreLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}

#define PLS_LOG_FATAL(...) SPDLOG_LOGGER_CRITICAL(Pulsarion::Log::GetLogger(), __VA_ARGS__)
#define PLS_LOG_ERROR(...) SPDLOG_LOGGER_ERROR(Pulsarion::Log::GetLogger(), __VA_ARGS__)
#define PLS_LOG_WARN(...) SPDLOG_LOGGER_WARN(Pulsarion::Log::GetLogger(), __VA_ARGS__)
#define PLS_LOG_INFO(...) SPDLOG_LOGGER_INFO(Pulsarion::Log::GetLogger(), __VA_ARGS__)
#define PLS_LOG_TRACE(...) SPDLOG_LOGGER_TRACE(Pulsarion::Log::GetLogger(), __VA_ARGS__)
#define PLS_LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(Pulsarion::Log::GetLogger(), __VA_ARGS__)

