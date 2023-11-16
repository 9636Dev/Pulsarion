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
    enum InputUniformType
    {
        Matrix4,
        Vector4,
        Vector3,
        Vector2,
        Sampler2D,
    };

    struct InputUniform
    {
        std::string Name;
        InputUniformType Type;
        bool FragmentShader;
    };

    static constexpr std::string GetTypeString(InputUniformType type)
    {
        switch (type)
        {
        case Matrix4:
            return "mat4";
        case Vector4:
            return "vec4";
        case Vector3:
            return "vec3";
        case Vector2:
            return "vec2";
        case Sampler2D:
            return "sampler2D";
        }
        PLS_LOG_ERROR("Invalid InputUniformType: {}", type);
        return "";
    }

    static constexpr std::array<InputUniform, 64> CreateUniformMap()
    {
        std::array<InputUniform, 64> map;
        map[0] = { "Position2D", InputUniformType::Vector2, false };
        map[1] = { "Position3D", InputUniformType::Vector3, false };
        map[2] = { "TextureCoord2D", InputUniformType::Vector2, true };
        map[3] = { "TextureCoord3D", InputUniformType::Vector3, true };

        map[32] = { "ModelMatrix", InputUniformType::Matrix4, false };
        map[33] = { "ViewMatrix", InputUniformType::Matrix4, false };
        map[34] = { "ProjectionMatrix", InputUniformType::Matrix4, false };
        map[35] = { "Texture2D", InputUniformType::Sampler2D, true };
        map[36] = { "DiffuseColor", InputUniformType::Vector4, true };
        return map;
    }

    std::shared_ptr<Shader> CreateShaderWithSignature(const ShaderSignature& signature)
    {
        // Check for overlap in input and uniform, return nullptr if there is overlap
        if ((signature.inputsBitmap & signature.uniformsBitmap) != 0)
            return nullptr;

        static const std::array<InputUniform, 64> uniformMap = CreateUniformMap();
        // Layout position of the inputs are in the order the InputUniforms are parsed
        std::vector<InputUniform> vertexInputs;
        std::vector<InputUniform> vertexUniforms;
        std::vector<InputUniform> vertexVaryings;
        std::vector<InputUniform> fragmentInputs;
        std::vector<InputUniform> fragmentUniforms;
        for (std::size_t i = 0; i < 64; ++i)
        {
            InputUniform iu = uniformMap[i];
            if ((signature.inputsBitmap & (1ull << i)) != 0)
            {
                if (uniformMap[i].FragmentShader)
                {
                    iu.Name = "v_" + iu.Name;
                    vertexVaryings.push_back(iu);
                    fragmentInputs.push_back(iu);
                }
                else
                {
                    iu.Name = "i_" + iu.Name;
                    vertexInputs.push_back(iu);
                }
            }

            if ((signature.uniformsBitmap & (1ull << i)) != 0)
            {
                iu.Name = "u_" + iu.Name;
                if (uniformMap[i].FragmentShader)
                    fragmentUniforms.push_back(iu);
                else
                    vertexUniforms.push_back(iu);
            }
        }

        std::string vertexShaderSource = "#version 330 core\n";
        for (std::uint16_t i = 0; i < vertexInputs.size(); ++i)
        {
            vertexShaderSource += "layout(location = " + std::to_string(i) + ") in " + GetTypeString(vertexInputs[i].Type) + " " + vertexInputs[i].Name + ";\n";
        }

        for (std::uint16_t i = 0; i < vertexVaryings.size(); ++i)
        {
            vertexShaderSource += "out " + GetTypeString(vertexVaryings[i].Type) + " " + vertexVaryings[i].Name + ";\n";
        }

        for (std::uint16_t i = 0; i < vertexUniforms.size(); ++i)
        {
            vertexShaderSource += "uniform " + GetTypeString(vertexUniforms[i].Type) + " " + vertexUniforms[i].Name + ";\n";
        }

        // Set varyings

        vertexShaderSource += "void main()\n{\n";

        for (std::uint16_t i = 0; i < vertexVaryings.size(); ++i)
        {
            vertexShaderSource += vertexVaryings[i].Name + " = " + vertexInputs[i].Name + ";\n";
        }

        if ((signature.inputsBitmap & (1ull << 0)) != 0)
            vertexShaderSource += "vec4 pos = vec4(" + vertexInputs[0].Name + ", 1.0, 1.0);\n";
        else if ((signature.inputsBitmap & (1ull << 1)) != 0)
            vertexShaderSource += "vec4 pos = vec4(" + vertexInputs[1].Name + ", 1.0);\n";
        else
        {
            PLS_LOG_ERROR("Vertex shader must have either position2D or position3D as input");
            return nullptr;
        }

        // Incrementally transform the position, popping the last transformation from the stack, in reverse order
        // Create a map of the inputs and uniforms, where the key has their prefix removed
        std::map<std::string, InputUniform> inputUniformMap;
        for (const InputUniform& iu : vertexInputs)
        {
            inputUniformMap[iu.Name.substr(2)] = iu;
        }

        for (const InputUniform& iu : vertexUniforms)
        {
            inputUniformMap[iu.Name.substr(2)] = iu;
        }

        // Error checking
        // Texture, but no texture coordinates
        if (inputUniformMap.find("Texture2D") != inputUniformMap.end() && inputUniformMap.find("TextureCoord2D") == inputUniformMap.end())
        {
            PLS_LOG_ERROR("Vertex shader has texture2D as input, but no textureCoord2D");
            return nullptr;
        }

        // Perform matrix multiplication in reverse order
        if (inputUniformMap.find("ModelMatrix") != inputUniformMap.end())
            vertexShaderSource += "pos = " + inputUniformMap["ModelMatrix"].Name + " * pos;\n";
        if (inputUniformMap.find("ViewMatrix") != inputUniformMap.end())
            vertexShaderSource += "pos = " + inputUniformMap["ViewMatrix"].Name + " * pos;\n";
        if (inputUniformMap.find("ProjectionMatrix") != inputUniformMap.end())
            vertexShaderSource += "pos = " + inputUniformMap["ProjectionMatrix"].Name + " * pos;\n";

        vertexShaderSource += "gl_Position = pos;\n";
        vertexShaderSource += "}\n";

        OpenGL::Shader vertexShader(OpenGL::ShaderType::VertexShader);
        vertexShader.ShaderSource(vertexShaderSource);
        if (!vertexShader.Compile())
        {
            PLS_LOG_ERROR("Failed to compile vertex shader: {}", vertexShader.GetInfoLog());
            return nullptr;
        }

        // Generate fragment shader
        std::string fragmentShaderSource = "#version 330 core\n";
        for (std::uint16_t i = 0; i < fragmentInputs.size(); ++i)
        {
            fragmentShaderSource += "in " + GetTypeString(fragmentInputs[i].Type) + " " + fragmentInputs[i].Name + ";\n";
        }

        for (std::uint16_t i = 0; i < fragmentUniforms.size(); ++i)
        {
            fragmentShaderSource += "uniform " + GetTypeString(fragmentUniforms[i].Type) + " " + fragmentUniforms[i].Name + ";\n";
        }

        fragmentShaderSource += "out vec4 fragColor;\n";

        fragmentShaderSource += "void main()\n{\n";

        // Map the inputs and uniforms to their names without prefixes
        inputUniformMap.clear();
        for (const InputUniform& iu : fragmentInputs)
        {
            inputUniformMap[iu.Name.substr(2)] = iu;
        }

        for (const InputUniform& iu : fragmentUniforms)
        {
            inputUniformMap[iu.Name.substr(2)] = iu;
        }
        fragmentShaderSource += "fragColor = vec4(1.0, 1.0, 1.0, 1.0);\n";

        if (inputUniformMap.find("Texture2D") != inputUniformMap.end() && inputUniformMap.find("TextureCoord2D") != inputUniformMap.end())
            fragmentShaderSource += "fragColor = fragColor * texture(" + inputUniformMap["Texture2D"].Name + ", " + inputUniformMap["TextureCoord2D"].Name + ");\n";
        if (inputUniformMap.find("DiffuseColor") != inputUniformMap.end())
            fragmentShaderSource += "fragColor = fragColor * " + inputUniformMap["DiffuseColor"].Name + ";\n";

        fragmentShaderSource += "}\n";

        OpenGL::Shader fragmentShader(OpenGL::ShaderType::FragmentShader);
        fragmentShader.ShaderSource(fragmentShaderSource);
        if (!fragmentShader.Compile())
        {
            PLS_LOG_ERROR("Failed to compile fragment shader: {}", fragmentShader.GetInfoLog());
        }

        // Print out source for debugging
        //PLS_LOG_DEBUG("Vertex shader source:\n{}", vertexShaderSource);
        //PLS_LOG_DEBUG("Fragment shader source:\n{}", fragmentShaderSource);

        std::vector<OpenGL::Shader> shaders;
        shaders.push_back(std::move(vertexShader));
        shaders.push_back(std::move(fragmentShader));

        return std::make_shared<OpenGL::GLShader>(std::move(shaders));
    }
}
