#pragma once

#include "Pulsarion/Core/Backend/OpenGL/GL.h"
#include "Pulsarion/Core/Backend/OpenGL/Enum.h"
#include "Pulsarion/Util/File.h"

#include <optional>
#include <map>
#include <cstdint>
#include <glm/glm.hpp>

namespace Pulsarion::OpenGL
{
    class Shader
    {
    public:
        friend class ShaderProgram;
        static std::optional<Shader> FromFile(ShaderType type,  const File& file);

        Shader(ShaderType type);
        ~Shader();
        Shader(const Shader& other) = delete;
        Shader(Shader&& other) noexcept;
        Shader& operator=(const Shader& other) = delete;
        Shader& operator=(Shader&& other) noexcept;

        void ShaderSource(const std::string& source);
        bool Compile();
        std::string GetInfoLog() const;
        std::string GetSource() const;
        ShaderType GetType() const;

        inline Shader_t GetHandle() const { return m_Shader; }

    private:
        Shader_t m_Shader;
        ShaderType m_Type;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram();
        ~ShaderProgram();

        void AttachShader(const Shader& shader);
        void DetachShader(const Shader& shader);
        bool Link();

        void Use() const;
        void Unuse() const;
        std::string GetInfoLog() const;
        
        void SetUniform(const std::string& name, float value);
        void SetUniform(const std::string& name, std::int32_t value);
        void SetUniform(const std::string& name, const glm::vec2& value);
        void SetUniform(const std::string& name, const glm::vec3& value);
        void SetUniform(const std::string& name, const glm::vec4& value);
        void SetUniform(const std::string& name, const glm::mat3& value);
        void SetUniform(const std::string& name, const glm::mat4& value);
    private:
        std::int32_t GetUniformLocation(const std::string& name) const;

        mutable std::map<std::string, std::int32_t> m_UniformLocations;
        Program_t m_Program;
    };
}
