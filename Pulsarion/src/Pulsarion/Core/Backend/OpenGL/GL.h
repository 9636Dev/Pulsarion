#pragma once

#include "Enum.h"
#include "Pulsarion/Util/Concepts.h"

#include <set>
#include <cstdint>

namespace Pulsarion::OpenGL
{
    using VertexArray_t = std::uint32_t;
    using Buffer_t = std::uint32_t;
    using Shader_t = std::uint32_t;
    using Program_t = std::uint32_t;
    using Texture_t = std::uint32_t;
    using sizei_t = std::int32_t;
    using sizeiptr_t = std::int64_t;

    struct GLVersion
    {
        std::int32_t Major;
        std::int32_t Minor;

        GLVersion() : Major(0), Minor(0) {}
    };

    struct GLFunctionCall
    {
        std::string Function;
        std::string File;
        std::uint32_t Line;

        GLFunctionCall(const std::string& function, const std::string& file, std::uint32_t line) : Function(function), File(file), Line(line) {}
    };

    class GL
    {
    public:
        static void Init(GLVersion& version);
        static void Terminate();

        template<Util::GLType T>
        static constexpr Type GetGLType();

        static void ClearColor(float r, float g, float b, float a);
        static void Clear(ClearTarget target);
        static void SetPolygonMode(PolygonFace face, PolygonMode mode);
        static void Enable(EnableTarget target);
        static void Disable(EnableTarget target);
        static void BlendFunc(BlendFactor sfactor, BlendFactor dfactor);

        static void GenVertexArrays(sizei_t n, VertexArray_t* arrays);
        static void GenBuffers(sizei_t n, Buffer_t* buffers);
        static void GenTextures(sizei_t n, Texture_t* textures);

        static void DeleteVertexArrays(sizei_t n, const VertexArray_t* arrays);
        static void DeleteBuffers(sizei_t n, const Buffer_t* buffers);
        static void DeleteTextures(sizei_t n, const Texture_t* textures);

        static void BindVertexArray(VertexArray_t array);
        static void BindBuffer(BufferTarget target, Buffer_t buffer);

        static void BufferData(BufferTarget target, sizeiptr_t size, const void* data, BufferUsage usage);
        static void BufferSubData(BufferTarget target, sizeiptr_t offset, sizeiptr_t size, const void* data);

        static void EnableVertexAttribArray(std::uint32_t index);
        static void DisableVertexAttribArray(std::uint32_t index);
        static void VertexAttribPointer(std::uint32_t index, std::int32_t size, Type type, bool normalized, sizei_t stride, const void* pointer);
        static void VertexAttribDivisor(std::uint32_t index, std::uint32_t divisor);

        [[nodiscard]] static Shader_t CreateShader(ShaderType type);
        static void DeleteShader(Shader_t shader);
        static void ShaderSource(Shader_t shader, sizei_t count, const char** string, const std::int32_t* length);
        static void CompileShader(Shader_t shader);
        static void GetShaderiv(Shader_t shader, ShaderParameter pname, std::int32_t* params);
        static void GetShaderInfoLog(Shader_t shader, sizei_t maxLength, sizei_t* length, char* infoLog);
        static void GetShaderSource(Shader_t shader, sizei_t maxLength, sizei_t* length, char* source);

        [[nodiscard]] static Program_t CreateProgram();
        static void DeleteProgram(Program_t program);
        static void AttachShader(Program_t program, Shader_t shader);
        static void DetachShader(Program_t program, Shader_t shader);
        static void LinkProgram(Program_t program);
        static void GetProgramiv(Program_t program, ProgramParameter pname, std::int32_t* params);
        static void GetProgramInfoLog(Program_t program, std::int32_t maxLength, std::int32_t* length, char* infoLog);
        static void UseProgram(Program_t program);

        static std::int32_t GetUniformLocation(Program_t program, const char* name);
        static void Uniform1i(std::int32_t location, std::int32_t v0);
        static void Uniform1f(std::int32_t location, float v0);
        static void Uniform2f(std::int32_t location, float v0, float v1);
        static void Uniform3f(std::int32_t location, float v0, float v1, float v2);
        static void Uniform4f(std::int32_t location, float v0, float v1, float v2, float v3);
        static void UniformMatrix3fv(std::int32_t location, std::int32_t count, bool transpose, const float* value);
        static void UniformMatrix4fv(std::int32_t location, std::int32_t count, bool transpose, const float* value);

        static void BindTexture(TextureTarget target, std::uint32_t texture);
        static void TexImage2D(TextureTarget target, std::int32_t level, InternalFormat internalFormat, std::int32_t width, std::int32_t height, std::int32_t border, PixelFormat format, PixelType type, const void* data);
        static void ActiveTexture(TextureUnit unit);
        static void TexParameteri(TextureTarget target, TextureParameter pname, std::int32_t param);

        [[nodiscard]] static bool IsVertexArray(VertexArray_t array, bool requireBound = false);
        [[nodiscard]] static bool IsBuffer(Buffer_t buffer, bool requireBound = false);
        [[nodiscard]] static bool IsProgram(std::uint32_t program);
        [[nodiscard]] static bool IsShader(std::uint32_t shader);
        static void SetLogLevel(std::uint32_t logLevel);
    private:
        static void PulsarGLCallback(std::uint32_t source, std::uint32_t type, std::uint32_t id, std::uint32_t severity, sizei_t msg_length, const char* message, const void* userParam);
        static void CheckError(const std::string& function, const std::string& file, std::uint32_t line);

        static std::set<VertexArray_t> s_VertexArrays;
        static std::set<Buffer_t> s_Buffers;
        static GLVersion s_Version;
        static GLFunctionCall s_LastFunction;
        static std::uint32_t s_LogLevel;
        static bool s_IsUsingDebugCallback;
        static VertexArray_t s_BoundVertexArray;
        static Program_t s_BoundProgram;
    };

    template<>
    inline Type GL::GetGLType<float>()
    {
        return Type::Float;
    }

    template<>
    inline Type GL::GetGLType<double>()
    {
        return Type::Double;
    }

    template<>
    inline Type GL::GetGLType<std::int32_t>()
    {
        return Type::Int;
    }

    template<>
    inline Type GL::GetGLType<std::uint32_t>()
    {
        return Type::UnsignedInt;
    }

    template<>
    inline Type GL::GetGLType<std::int16_t>()
    {
        return Type::Short;
    }

    template<>
    inline Type GL::GetGLType<std::uint16_t>()
    {
        return Type::UnsignedShort;
    }

    template<>
    inline Type GL::GetGLType<std::int8_t>()
    {
        return Type::Byte;
    }

    template<>
    inline Type GL::GetGLType<std::uint8_t>()
    {
        return Type::UnsignedByte;
    }
}
