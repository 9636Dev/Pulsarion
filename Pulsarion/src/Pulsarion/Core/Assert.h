#pragma once

#ifdef PLS_ENABLE_ASSERTS
#define PLS_INTERNAL_ASSERT_IMPL(check, msg, ...) { if(!(check)) { PLS_LOG_ERROR(msg, __VA_ARGS__); PLS_DEBUGBREAK(); } }
#define PLS_INTERNAL_ASSERT_WITH_MSG(check, ...) PLS_INTERNAL_ASSERT_IMPL(check, "Assertion failed: {0}", __VA_ARGS__)
#define PLS_INTERNAL_ASSERT_NO_MSG(check) PLS_INTERNAL_ASSERT_IMPL(check, "Assertion '{0}' failed at {1}:{2}", PLS_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define PLS_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define PLS_INTERNAL_ASSERT_GET_MACRO(...) PLS_EXPAND_MACRO( PLS_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, PLS_INTERNAL_ASSERT_WITH_MSG, PLS_INTERNAL_ASSERT_NO_MSG) )

#define PLS_CORE_ASSERT(...) PLS_EXPAND_MACRO( PLS_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
#define PLS_ASSERT(...)
#define PLS_CORE_ASSERT(...)
#endif
