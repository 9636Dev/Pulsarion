#pragma once

#ifdef PLS_PLATFORM_WINDOWS
#ifdef PLS_BUILD_DLL
#define PULSARION_API __declspec(dllexport)
#else
#define PULSARION_API __declspec(dllimport)
#endif
#elif defined(PLS_PLATFORM_MACOS)
#ifdef PLS_BUILD_DLL
#define PULSARION_API __attribute__((visibility("default")))
#else
#define PULSARION_API
#endif
#else
#error Pulsarion only supports Windows and MacOS!
#endif

#ifdef PLS_DEBUG
#if defined(PLS_PLATFORM_WINDOWS)
#define PLS_DEBUGBREAK() __debugbreak()
#elif defined(PLS_PLATFORM_MACOS)
#define PLS_DEBUGBREAK() __builtin_trap()
#else
#error "Platform doesn't support debugbreak yet!"
#endif

#define PLS_EXPAND_MACRO(x) x
#define PLS_STRINGIFY_MACRO(x) #x
#define PLS_RUN_IF_DEBUG(x) if constexpr (PLS_DEBUG) { x; }

#define PLS_ENABLE_ASSERTS
#define SPD_LOG_ACTIVE_LEVEL 0
#else
#define PLS_DEBUGBREAK()
#endif

#if defined(PLS_ENABLE_ASSERTS) && !defined(PLS_DISABLE_ASSERTS)
#include "Assert.h"
#endif


// Backends
#ifdef PLS_PLATFORM_WINDOWS
#define PLS_USE_GLFW_WINDOW
#define PLS_USE_OPENGL_RENDERER
#elif defined(PLS_PLATFORM_MACOS)
#define PLS_USE_GLFW_WINDOW
#define PLS_USE_OPENGL_RENDERER
#endif

namespace Pulsarion
{
    class PULSARION_API Initializers
    {
    public:
        static void InitLogger();
    };
}
