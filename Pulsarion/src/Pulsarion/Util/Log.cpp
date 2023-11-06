#include "Pulsarionpch.h"
#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/pattern_formatter.h>

namespace Pulsarion {

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;

    void Log::Init()
    {
        static bool s_Initialized = false;
        if (s_Initialized)
            return;
        s_Initialized = true;
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("PULSARION");
        s_CoreLogger->set_level(spdlog::level::trace);
        
        auto formatter = std::make_unique<spdlog::pattern_formatter>();
        formatter->set_pattern("%^[%T] %s:%# [%n] %v%$");
        s_CoreLogger->set_formatter(std::move(formatter));
    }
}
