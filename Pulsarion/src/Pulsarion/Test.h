#pragma once

#ifdef PLS_BUILD_DLL
#define PULSARION_API __declspec(dllexport)
#else
#define PULSARION_API __declspec(dllimport)
#endif

PULSARION_API int Test();