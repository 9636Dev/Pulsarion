#include "Pulsarionpch.h"
#include "GL.h"

#include <GL/glew.h>

namespace Pulsarion::OpenGL
{
#ifdef PLS_DEBUG
    #define PLS_GLCall(func, ...) do { func(__VA_ARGS__); CheckError(#func, __LINE__); } while (0)
    #define PLS_GLCallR(func, ...) [&]() { auto result = func(__VA_ARGS__); CheckError(#func, __LINE__); return result; }()
#else
    #define PLS_GLCall(func, ...) func(__VA_ARGS__)
    #define PLS_GLCallR(func, ...) func(__VA_ARGS__)
#endif

    std::set<VertexArray_t> GL::s_VertexArrays;
    std::set<Buffer_t> GL::s_Buffers;
    GLVersion GL::s_Version;
    GLFunctionCall GL::s_LastFunction("null", __FILE__, __LINE__);
    bool GL::s_IsUsingDebugCallback = false;
    std::uint32_t GL::s_LogLevel = 0;

    void GL::Init(GLVersion& version)
    {
        static bool s_Initialized = false;
        if (s_Initialized)
            return;
        
        GLenum result = glewInit();
        if (result != GLEW_OK)
        {
            PLS_LOG_ERROR("[GL] Could not initialize GLEW! (Enum value: {})", result);

            version.Major = 0;
            version.Minor = 0;
            return; // Don't abort here, because the handling will be down by the window class.
        }

        // Print version string
        const char* versionString = (const char*)glGetString(GL_VERSION);
        PLS_LOG_INFO("[GL] Using OpenGL version: {}", versionString);
        // Do I have to delete the string?

        glGetIntegerv(GL_MAJOR_VERSION, &version.Major);
        glGetIntegerv(GL_MINOR_VERSION, &version.Minor);

        PLS_LOG_DEBUG("[GL] Initialized OpenGL version {}.{}", version.Major, version.Minor);
        s_Version = version;
        s_Initialized = true;

        // Callbacks
        if (s_Version.Major >= 4 && s_Version.Minor >= 3)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(PulsarGLCallback, nullptr);
            s_IsUsingDebugCallback = true;
            PLS_LOG_DEBUG("[GL] Using OpenGL 4.3+ debug callback");
        }
        else if (glewIsSupported("GL_ARB_debug_output"))
        {
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
            glDebugMessageCallbackARB(PulsarGLCallback, nullptr);
            s_IsUsingDebugCallback = true;
            PLS_LOG_DEBUG("[GL] Using OpenGL 4.3 ARB debug callback");
        }
        else
        {
            PLS_LOG_INFO("[GL] Could not enable debug callback!");
            s_IsUsingDebugCallback = false;
        }
    }

    void GL::Terminate()
    {
        PLS_LOG_INFO("[GL] Terminating OpenGL");
    }

    void GL::CheckError(const std::string& function, const std::string& file, std::uint32_t line)
    {
        if (s_IsUsingDebugCallback)
        {
            s_LastFunction = GLFunctionCall(function, file, line);
            return;
        }

        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            PLS_LOG_ERROR("[GL] Error in function {} at line {}: {}", function, line, error);
            s_LastFunction = GLFunctionCall(function, file, line);
        }
    }

    void GL::PulsarGLCallback(std::uint32_t source, std::uint32_t type, std::uint32_t id, std::uint32_t severity, sizei_t msg_length, const char* message, const void* userParam)
    {
        unsigned int severity_int;
        std::string severity_str;
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            severity_int = 3;
            severity_str = "HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severity_int = 2;
            severity_str = "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severity_int = 1;
            severity_str = "LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severity_int = 0;
            severity_str = "NOTIFICATION";
            break;
        }

        if (severity_int < s_LogLevel) return; // Only log if severity is high enough
        std::string source_str;
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            source_str = "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            source_str = "WINDOW_SYSTEM";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            source_str = "SHADER_COMPILER";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            source_str = "THIRD_PARTY";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            source_str = "APPLICATION";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            source_str = "OTHER";
            break;
        }

        std::string type_str;
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            type_str = "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            type_str = "DEPRECATED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            type_str = "UNDEFINED_BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            type_str = "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            type_str = "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_MARKER:
            type_str = "MARKER";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            type_str = "PUSH_GROUP";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            type_str = "POP_GROUP";
            break;
        case GL_DEBUG_TYPE_OTHER:
            type_str = "OTHER";
            break;
        }

        if (msg_length == 0) message = "(Empty Message)";
        else if (msg_length == -1) message = "(Message Truncated)";

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            PLS_LOG_ERROR("[OpenGL Error] Source: {0}, Type: {1}, Id: {2}, Severity: {3}, Message: {4}", source_str, type_str, id, severity_str, message);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            PLS_LOG_WARN("[OpenGL Error] Source: {0}, Type: {1}, Id: {2}, Severity: {3}, Message: {4}", source_str, type_str, id, severity_str, message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            PLS_LOG_INFO("[OpenGL Error] Source: {0}, Type: {1}, Id: {2}, Severity: {3}, Message: {4}", source_str, type_str, id, severity_str, message);
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            PLS_LOG_TRACE("[OpenGL Error] Source: {0}, Type: {1}, Id: {2}, Severity: {3}, Message: {4}", source_str, type_str, id, severity_str, message);
            break;
        }
        PLS_LOG_DEBUG("[GL] GLCall: {0}, at {1}:{2}", s_LastFunction.Function, s_LastFunction.File, s_LastFunction.Line);

        if (type == GL_DEBUG_TYPE_PERFORMANCE) return;
        if (severity_int > 0) PLS_DEBUGBREAK();
    }
}
