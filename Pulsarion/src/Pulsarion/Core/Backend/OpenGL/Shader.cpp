#include "Pulsarionpch.h"
#include "Shader.h"

namespace Pulsarion::OpenGL
{
    std::optional<Shader> Shader::FromFile(ShaderType type, const File& file)
    {
        std::optional<std::string> content = file.GetContent();
        if (!content)
            return std::nullopt;

        std::optional<Shader> shader = std::make_optional<Shader>(type);
        shader->ShaderSource(content.value());
        return shader;
    }

    Shader::Shader(ShaderType type) : m_Shader(GL::CreateShader(type)), m_Type(type)
    {

    }

    Shader::Shader(Shader&& other) noexcept : m_Shader(other.m_Shader), m_Type(other.m_Type)
    {
        other.m_Shader = 0;
    }

    Shader& Shader::operator=(Shader&& other) noexcept
    {
        m_Shader = other.m_Shader;
        m_Type = other.m_Type;
        other.m_Shader = 0;
        return *this;
    }

    Shader::~Shader()
    {
        GL::DeleteShader(m_Shader);
    }

    void Shader::ShaderSource(const std::string& source)
    {
        const char* src = source.c_str();
        GL::ShaderSource(m_Shader, 1, &src, nullptr);
    }

    bool Shader::Compile()
    {
        GL::CompileShader(m_Shader);
        std::int32_t status;
        GL::GetShaderiv(m_Shader, ShaderParameter::CompileStatus, &status);
        return status;
    }

    std::string Shader::GetInfoLog() const
    {
        std::int32_t length;
        GL::GetShaderiv(m_Shader, ShaderParameter::InfoLogLength, &length);
        std::string infoLog(length, '\0');
        GL::GetShaderInfoLog(m_Shader, length, &length, infoLog.data());
        return infoLog;
    }

    std::string Shader::GetSource() const
    {
        std::int32_t length;
        GL::GetShaderiv(m_Shader, ShaderParameter::ShaderSourceLength, &length);
        std::string source(length, '\0');
        GL::GetShaderSource(m_Shader, length, &length, source.data());
        return source;
    }

    ShaderType Shader::GetType() const
    {
        return m_Type;
    }

    ShaderProgram::ShaderProgram() : m_Program(GL::CreateProgram())
    {

    }

    ShaderProgram::~ShaderProgram()
    {
        GL::DeleteProgram(m_Program);
    }

    void ShaderProgram::AttachShader(const Shader& shader)
    {
        GL::AttachShader(m_Program, shader.m_Shader);
    }

    void ShaderProgram::DetachShader(const Shader& shader)
    {
        GL::DetachShader(m_Program, shader.m_Shader);
    }

    bool ShaderProgram::Link()
    {
        GL::LinkProgram(m_Program);
        std::int32_t status;
        GL::GetProgramiv(m_Program, ProgramParameter::LinkStatus, &status);
        return status;
    }

    void ShaderProgram::Use() const
    {
        GL::UseProgram(m_Program);
    }

    void ShaderProgram::Unuse() const
    {
        GL::UseProgram(0);
    }

    std::string ShaderProgram::GetInfoLog() const
    {
        std::int32_t length;
        GL::GetProgramiv(m_Program, ProgramParameter::InfoLogLength, &length);
        std::string infoLog(length, '\0');
        GL::GetProgramInfoLog(m_Program, length, &length, infoLog.data());
        return infoLog;
    }

    std::int32_t ShaderProgram::GetUniformLocation(const std::string& name) const
    {
        if (m_UniformLocations.find(name) != m_UniformLocations.end())
            return m_UniformLocations[name];
        std::int32_t location = GL::GetUniformLocation(m_Program, name.c_str());
        m_UniformLocations[name] = location;
        return location;
    }

    void ShaderProgram::SetUniform(const std::string& name, std::int32_t value)
    {
        // Don't bind the program here, because it might be bound already for performance reasons
        PLS_CORE_ASSERT(GL::GetBoundProgram() == m_Program, "ShaderProgram::SetUniform: ShaderProgram is not bound!");
        GL::Uniform1i(GetUniformLocation(name), value);
    }

    void ShaderProgram::SetUniform(const std::string& name, float value)
    {
        PLS_CORE_ASSERT(GL::GetBoundProgram() == m_Program, "ShaderProgram::SetUniform: ShaderProgram is not bound!");
        GL::Uniform1f(GetUniformLocation(name), value);
    }

    void ShaderProgram::SetUniform(const std::string& name, const glm::vec2& value)
    {
        PLS_CORE_ASSERT(GL::GetBoundProgram() == m_Program, "ShaderProgram::SetUniform: ShaderProgram is not bound!");
        GL::Uniform2f(GetUniformLocation(name), value.x, value.y);
    }

    void ShaderProgram::SetUniform(const std::string& name, const glm::vec3& value)
    {
        PLS_CORE_ASSERT(GL::GetBoundProgram() == m_Program, "ShaderProgram::SetUniform: ShaderProgram is not bound!");
        GL::Uniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    }

    void ShaderProgram::SetUniform(const std::string& name, const glm::vec4& value)
    {
        PLS_CORE_ASSERT(GL::GetBoundProgram() == m_Program, "ShaderProgram::SetUniform: ShaderProgram is not bound!");
        GL::Uniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void ShaderProgram::SetUniform(const std::string& name, const glm::mat3& value)
    {
        PLS_CORE_ASSERT(GL::GetBoundProgram() == m_Program, "ShaderProgram::SetUniform: ShaderProgram is not bound!");
        GL::UniformMatrix3fv(GetUniformLocation(name), 1, false, glm::value_ptr(value));
    }

    void ShaderProgram::SetUniform(const std::string& name, const glm::mat4& value)
    {
        PLS_CORE_ASSERT(GL::GetBoundProgram() == m_Program, "ShaderProgram::SetUniform: ShaderProgram is not bound!");
        GL::UniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(value));
    }
}
