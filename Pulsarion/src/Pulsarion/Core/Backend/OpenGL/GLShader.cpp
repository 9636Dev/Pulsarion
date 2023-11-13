#include "Pulsarionpch.h"
#include "GLShader.h"

#include "Shader.h"

namespace Pulsarion::OpenGL
{
    GLShader::GLShader(std::vector<OpenGL::Shader>&& shaders) : m_Shaders(std::move(shaders)), m_Program()
    {
        for (const OpenGL::Shader& shader : m_Shaders)
        {
            m_Program.AttachShader(shader);
        }

        if (!m_Program.Link())
        {
            PLS_LOG_ERROR("Failed to link shader program: {}", m_Program.GetInfoLog());
        }
    }

    GLShader::~GLShader()
    {

    }

    void GLShader::Bind() const
    {
        m_Program.Use();
    }

    void GLShader::Unbind() const
    {
        m_Program.Unuse();
    }

    void GLShader::SetUniform(const std::string& name, const glm::mat4& value)
    {
        m_Program.SetUniform(name, value);
    }

    void GLShader::SetUniform(const std::string& name, const glm::vec4& value)
    {
        m_Program.SetUniform(name, value);
    }

    void GLShader::SetUniform(const std::string& name, const glm::vec3& value)
    {
        m_Program.SetUniform(name, value);
    }

    void GLShader::SetUniform(const std::string& name, std::int32_t value)
    {
        m_Program.SetUniform(name, value);
    }
}


namespace Pulsarion
{
    std::shared_ptr<Shader> CreateShaderWithSignature(const ShaderSignature& signature)
    {
        // Currently only support inputs position, texcoord and uniform texture, modelMatrix, diffuseColor
        if (signature.inputsBitmap == 0x0000000000000005 && signature.uniformsBitmap == 0x0000001900000000)
        {
            std::optional<OpenGL::Shader> vertexShaderOpt = OpenGL::Shader::FromFile(OpenGL::ShaderType::VertexShader, File("assets/shaders/basic_textured_vertex.glsl"));
            if (!vertexShaderOpt)
            {
                PLS_LOG_ERROR("Failed to load vertex shader");
                return nullptr;
            }
            OpenGL::Shader vertexShader = std::move(vertexShaderOpt.value());

            if (!vertexShader.Compile())
            {
                PLS_LOG_ERROR("Failed to compile vertex shader: {}", vertexShader.GetInfoLog());
            }
            std::optional<OpenGL::Shader> fragmentShaderOpt = OpenGL::Shader::FromFile(OpenGL::ShaderType::FragmentShader, File("assets/shaders/basic_textured_fragment.glsl"));
            if (!fragmentShaderOpt)
            {
                PLS_LOG_ERROR("Failed to load fragment shader");
                return nullptr;
            }

            OpenGL::Shader fragmentShader = std::move(fragmentShaderOpt.value());
            if (!fragmentShader.Compile())
            {
                PLS_LOG_ERROR("Failed to compile fragment shader: {}", fragmentShader.GetInfoLog());
            }

            std::vector<OpenGL::Shader> shaders;
            shaders.push_back(std::move(vertexShader));
            shaders.push_back(std::move(fragmentShader));

            return std::make_shared<OpenGL::GLShader>(std::move(shaders));
        }
        return nullptr;
    }
}
