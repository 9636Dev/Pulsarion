#include "Pulsarionpch.h"
#include "GL.h"

#include <GL/glew.h>

namespace Pulsarion::OpenGL
{
#ifdef PLS_DEBUG
    #define PLS_GLCall(func, ...) do { func(__VA_ARGS__); CheckError(#func, __FILE__, __LINE__); } while (0)
    #define PLS_GLCallR(func, ...) [&]() { auto result = func(__VA_ARGS__); CheckError(#func, __FILE__, __LINE__); return result; }()
#else
    #define PLS_GLCall(func, ...) func(__VA_ARGS__)
    #define PLS_GLCallR(func, ...) func(__VA_ARGS__)
#endif

    std::set<VertexArray_t> GL::s_VertexArrays;
    std::set<Buffer_t> GL::s_Buffers;
    GLVersion GL::s_Version;
    GLFunctionCall GL::s_LastFunction("null", __FILE__, __LINE__);
    bool GL::s_IsUsingDebugCallback = false;
    std::uint32_t GL::s_LogLevel = 1;
    VertexArray_t GL::s_BoundVertexArray = 0;
    Program_t GL::s_BoundProgram = 0;

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

    void GL::ClearColor(float r, float g, float b, float a)
    {
        PLS_GLCall(glClearColor, r, g, b, a);
    }

    void GL::Clear(ClearTarget target)
    {
        PLS_GLCall(glClear, static_cast<std::uint32_t>(target));
    }

    void GL::SetPolygonMode(PolygonFace face, PolygonMode mode)
    {
        PLS_GLCall(glPolygonMode, static_cast<std::uint32_t>(face), static_cast<std::uint32_t>(mode));
    }

    void GL::Enable(EnableTarget target)
    {
        PLS_GLCall(glEnable, static_cast<std::uint32_t>(target));
    }

    void GL::Disable(EnableTarget target)
    {
        PLS_GLCall(glDisable, static_cast<std::uint32_t>(target));
    }

    void GL::BlendFunc(BlendFactor sfactor, BlendFactor dfactor)
    {
        PLS_GLCall(glBlendFunc, static_cast<std::uint32_t>(sfactor), static_cast<std::uint32_t>(dfactor));
    }

    void GL::GenVertexArrays(sizei_t n, VertexArray_t *arrays)
    {
        PLS_GLCall(glGenVertexArrays, n, arrays);
        PLS_RUN_IF_DEBUG(for (sizei_t i = 0; i < n; i++)
            s_VertexArrays.insert(arrays[i]));
    }

    void GL::DeleteVertexArrays(sizei_t n, const VertexArray_t *arrays)
    {
        PLS_GLCall(glDeleteVertexArrays, n, arrays);
        PLS_RUN_IF_DEBUG(for (sizei_t i = 0; i < n; i++)
            s_VertexArrays.erase(arrays[i]));
    }

    void GL::BindVertexArray(VertexArray_t array)
    {
        if (s_BoundVertexArray == array) return;
        s_BoundVertexArray = array;
        PLS_GLCall(glBindVertexArray, array);
    }

    void GL::GenBuffers(sizei_t n, Buffer_t *buffers)
    {
        PLS_GLCall(glGenBuffers, n, buffers);
        PLS_RUN_IF_DEBUG(for (sizei_t i = 0; i < n; i++)
            s_Buffers.insert(buffers[i]));
    }

    void GL::DeleteBuffers(sizei_t n, const Buffer_t *buffers)
    {
        PLS_GLCall(glDeleteBuffers, n, buffers);
        PLS_RUN_IF_DEBUG(for (sizei_t i = 0; i < n; i++)
            s_Buffers.erase(buffers[i]));
    }

    void GL::BindBuffer(BufferTarget target, Buffer_t buffer)
    {
        PLS_GLCall(glBindBuffer, static_cast<std::uint32_t>(target), buffer);
    }

    void GL::BufferData(BufferTarget target, sizeiptr_t size, const void *data, BufferUsage usage)
    {
        PLS_GLCall(glBufferData, static_cast<std::uint32_t>(target), size, data, static_cast<std::uint32_t>(usage));
    }

    void GL::BufferSubData(BufferTarget target, sizeiptr_t offset, sizeiptr_t size, const void *data)
    {
        PLS_GLCall(glBufferSubData, static_cast<std::uint32_t>(target), offset, size, data);
    }

    void GL::EnableVertexAttribArray(std::uint32_t index)
    {
        PLS_GLCall(glEnableVertexAttribArray, index);
    }

    void GL::DisableVertexAttribArray(std::uint32_t index)
    {
        PLS_GLCall(glDisableVertexAttribArray, index);
    }

    void GL::VertexAttribPointer(std::uint32_t index, std::int32_t size, Type type, bool normalized, sizei_t stride, const void *pointer)
    {
        PLS_GLCall(glVertexAttribPointer, index, size, static_cast<std::uint32_t>(type), normalized, stride, pointer);
    }

    void GL::VertexAttribDivisor(std::uint32_t index, std::uint32_t divisor)
    {
        PLS_GLCall(glVertexAttribDivisor, index, divisor);
    }

    Shader_t GL::CreateShader(ShaderType type)
    {
        return PLS_GLCallR(glCreateShader, static_cast<std::uint32_t>(type));
    }

    void GL::DeleteShader(Shader_t shader)
    {
        PLS_GLCall(glDeleteShader, shader);
    }

    void GL::ShaderSource(Shader_t shader, sizei_t count, const char** string, const std::int32_t* length)
    {
        PLS_GLCall(glShaderSource, shader, count, string, length);
    }

    void GL::CompileShader(Shader_t shader)
    {
        PLS_GLCall(glCompileShader, shader);
    }

    void GL::GetShaderiv(Shader_t shader, ShaderParameter pname, std::int32_t *params)
    {
        PLS_GLCall(glGetShaderiv, shader, static_cast<std::uint32_t>(pname), params);
    }

    void GL::GetShaderInfoLog(Shader_t shader, sizei_t bufSize, sizei_t *length, char *infoLog)
    {
        PLS_GLCall(glGetShaderInfoLog, shader, bufSize, length, infoLog);
    }

    void GL::GetShaderSource(Shader_t shader, sizei_t bufSize, sizei_t *length, char *source)
    {
        PLS_GLCall(glGetShaderSource, shader, bufSize, length, source);
    }

    Program_t GL::CreateProgram()
    {
        return PLS_GLCallR(glCreateProgram);
    }

    void GL::DeleteProgram(Program_t program)
    {
        PLS_GLCall(glDeleteProgram, program);
    }

    void GL::GetProgramiv(Program_t program, ProgramParameter pname, std::int32_t* params)
    {
        PLS_GLCall(glGetProgramiv, program, static_cast<std::uint32_t>(pname), params);
    }

    void GL::GetProgramInfoLog(Program_t program, std::int32_t bufSize, std::int32_t* length, char* infoLog)
    {
        PLS_GLCall(glGetProgramInfoLog, program, bufSize, length, infoLog);
    }

    void GL::AttachShader(Program_t program, Shader_t shader)
    {
        PLS_GLCall(glAttachShader, program, shader);
    }

    void GL::DetachShader(Program_t program, Shader_t shader)
    {
        PLS_GLCall(glDetachShader, program, shader);
    }

    void GL::LinkProgram(Program_t program)
    {
        PLS_GLCall(glLinkProgram, program);
    }

    void GL::UseProgram(Program_t program)
    {
        if (program == s_BoundProgram) return;
        PLS_GLCall(glUseProgram, program);
        s_BoundProgram = program;
    }

    std::int32_t GL::GetUniformLocation(Program_t program, const char* name)
    {
        return PLS_GLCallR(glGetUniformLocation, program, name);
    }

    void GL::Uniform1i(std::int32_t location, std::int32_t v0)
    {
        PLS_GLCall(glUniform1i, location, v0);
    }

    void GL::Uniform1f(std::int32_t location, float v0)
    {
        PLS_GLCall(glUniform1f, location, v0);
    }

    void GL::Uniform2f(std::int32_t location, float v0, float v1)
    {
        PLS_GLCall(glUniform2f, location, v0, v1);
    }

    void GL::Uniform3f(std::int32_t location, float v0, float v1, float v2)
    {
        PLS_GLCall(glUniform3f, location, v0, v1, v2);
    }

    void GL::Uniform4f(std::int32_t location, float v0, float v1, float v2, float v3)
    {
        PLS_GLCall(glUniform4f, location, v0, v1, v2, v3);
    }

    void GL::UniformMatrix3fv(std::int32_t location, std::int32_t count, bool transpose, const float* value)
    {
        PLS_GLCall(glUniformMatrix3fv, location, count, transpose, value);
    }

    void GL::UniformMatrix4fv(std::int32_t location, std::int32_t count, bool transpose, const float* value)
    {
        PLS_GLCall(glUniformMatrix4fv, location, count, transpose, value);
    }

    void GL::GenTextures(sizei_t n, std::uint32_t* textures)
    {
        PLS_GLCall(glGenTextures, n, textures);
    }

    void GL::DeleteTextures(sizei_t n, const std::uint32_t* textures)
    {
        PLS_GLCall(glDeleteTextures, n, textures);
    }

    void GL::BindTexture(TextureTarget target, std::uint32_t texture)
    {
        PLS_GLCall(glBindTexture, static_cast<std::uint32_t>(target), texture);
    }

    void GL::TexImage2D(TextureTarget target, std::int32_t level, InternalFormat internalFormat, std::int32_t width, std::int32_t height, std::int32_t border, PixelFormat format, PixelType type, const void* data)
    {
        PLS_GLCall(glTexImage2D, static_cast<std::uint32_t>(target), level, static_cast<std::uint32_t>(internalFormat), width, height, border, static_cast<std::uint32_t>(format), static_cast<std::uint32_t>(type), data);
    }

    void GL::ActiveTexture(TextureUnit unit)
    {
        PLS_GLCall(glActiveTexture, static_cast<std::uint32_t>(unit));
    }

    void GL::TexParameteri(TextureTarget target, TextureParameter pname, std::int32_t param)
    {
        PLS_GLCall(glTexParameteri, static_cast<std::uint32_t>(target), static_cast<std::uint32_t>(pname), param);
    }

    void GL::SetLogLevel(std::uint32_t logLevel)
    {
        s_LogLevel = logLevel;
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
