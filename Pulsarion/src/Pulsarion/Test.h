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
#error Pulsarion only supports Windows and macOS!
#endif

class PULSARION_API Test
{
public:
    static int Run();
};
