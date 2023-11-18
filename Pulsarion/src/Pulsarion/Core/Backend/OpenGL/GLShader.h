#pragma once

#include "Pulsarion/Util/File.h"
#include "Pulsarion/Core/Shader.h"
#include "Pulsarion/Core/Backend/OpenGL/Shader.h"

#include <vector>

namespace Pulsarion::OpenGL
{
    class GLShader : public ::Pulsarion::Shader
    {
    public:
        GLShader(std::vector<OpenGL::Shader>&& shaders, const Shading::ShaderSignature& signature, const Shading::ShaderInputOrder& inputOrder);
        ~GLShader();

        void Bind() const override;
        void Unbind() const override;

        void SetUniform(const std::string& name, const glm::mat4& matrix) override;
        void SetUniform(const std::string& name, const glm::vec4& vector) override;
        void SetUniform(const std::string& name, const glm::vec3& vector) override;
        void SetUniform(const std::string& name, std::int32_t) override;
    private:
        ShaderProgram m_Program;
        std::vector<OpenGL::Shader> m_Shaders;
    };
}
