#include "Pulsarionpch.h"
#include "GLShader.h"

#include "Shader.h"

namespace Pulsarion::OpenGL
{
    GLShader::GLShader(std::vector<OpenGL::Shader>&& shaders, const Shading::ShaderSignature& signature, const Shading::ShaderInputOrder& inputOrder) : Shader(Shading::ShaderSignature(), inputOrder), m_Shaders(std::move(shaders)), m_Program()
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
        std::uint32_t NumericalRepr;
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
        map[0] = { "Position2D", InputUniformType::Vector2, 1 << 0};
        map[1] = { "Position3D", InputUniformType::Vector3, 1 << 1};
        map[2] = { "TextureCoord2D", InputUniformType::Vector2, 1 << 2 };
        map[3] = { "TextureCoord3D", InputUniformType::Vector3, 1 << 3 };
        map[4] = { "Normal2D", InputUniformType::Vector2, 1 << 4 };
        map[5] = { "Normal3D", InputUniformType::Vector3, 1 << 5 };
        map[6] = { "Tangent2D", InputUniformType::Vector2, 1 << 6 };
        map[7] = { "Tangent3D", InputUniformType::Vector3, 1 << 7 };
        map[8] = { "Bitangent2D", InputUniformType::Vector2, 1 << 8 };
        map[9] = { "Bitangent3D", InputUniformType::Vector3, 1 << 9 };
        map[10] = { "ModelMatrix", InputUniformType::Matrix4, 1 << 10 };
        map[11] = { "ViewMatrix", InputUniformType::Matrix4, 1 << 11 };
        map[12] = { "ProjectionMatrix", InputUniformType::Matrix4, 1 << 12 };
        map[13] = { "Texture2D", InputUniformType::Sampler2D, 1 << 13 };
        map[14] = { "DiffuseColor", InputUniformType::Vector4, 1 << 14 };

        return map;
    }

    struct ShaderIO
    {
        struct InputElement
        {
            InputUniform Input;
            std::uint16_t Index;
        };

        std::vector<InputElement> VertexInputs;
        std::vector<InputUniform> VertexUniforms;
        std::vector<InputElement> VertexVaryings;
        std::vector<InputUniform> FragmentUniforms;

        std::string GetVertexInputOrUniformName(std::string name, bool remove)
        {
            auto it = std::find_if(VertexInputs.begin(), VertexInputs.end(), [&name](const InputElement& element) { return element.Input.Name == name; });
            if (it != VertexInputs.end())
            {
                if (remove)
                    VertexInputs.erase(it);
                return "i_" + name;
            }

            auto it2 = std::find_if(VertexUniforms.begin(), VertexUniforms.end(), [&name](const InputUniform& uniform) { return uniform.Name == name; });
            if (it2 != VertexUniforms.end())
            {
                if (remove)
                    VertexUniforms.erase(it2);
                return "u_" + name;
            }

            return "";
        }

        std::string GenerateVertexInputs(bool& success)
        {
            std::vector<std::string> inputs;
            inputs.reserve(VertexInputs.size() + VertexVaryings.size());
            for (const InputElement& input : VertexInputs)
            {
                if (input.Input.Type == InputUniformType::Matrix4)
                {
                    // Check that the next 4 indices are free
                    for (std::uint16_t i = 0; i < 4; ++i)
                    {
                        if (i != 0 && std::find_if(VertexInputs.begin(), VertexInputs.end(), [input, i](const InputElement& element) { return element.Index == input.Index + i; }) != VertexInputs.end())
                        {
                            PLS_LOG_ERROR("Matrix4 input {} is not aligned (It will take 4 inputs)", input.Input.Name);
                            success = false;
                            return "";
                        }
                        inputs.push_back("layout (location=" + std::to_string(input.Index + i) + ") in vec4 i_" + input.Input.Name + "_C" + std::to_string(i));
                    }
                    continue;
                }
                inputs.push_back("layout (location=" + std::to_string(input.Index) + ") in " + GetTypeString(input.Input.Type) + " i_" + input.Input.Name);
            }

            for (const InputElement& input : VertexVaryings)
            {
                inputs.push_back("layout (location=" + std::to_string(input.Index) + ") in " + GetTypeString(input.Input.Type) + " i_" + input.Input.Name);
            }

            std::string result;
            for (const std::string& input : inputs)
            {
                result += input + ";\n";
            }

            success = true;
            return result;
        }

        std::string GenerateVertexUniforms()
        {
            std::string result;
            for (const InputUniform& uniform : VertexUniforms)
            {
                result += "uniform " + GetTypeString(uniform.Type) + " u_" + uniform.Name + ";\n";
            }

            return result;
        }

        std::string GenerateConversions(bool& success)
        {
            std::string result;
            auto table = CreateUniformMap();

            // Convert input to vec4, and matrix columns to mat4
            auto it = std::find_if(VertexInputs.begin(), VertexInputs.end(), [](const InputElement& element) { return element.Input.Name == "Position2D"; });
            if (it != VertexInputs.end())
            {
                result += "vec4 i_Position = vec4(i_Position2D, 1.0, 1.0);\n";
            }

            auto it2 = std::find_if(VertexInputs.begin(), VertexInputs.end(), [](const InputElement& element) { return element.Input.Name == "Position3D"; });
            if (it2 != VertexInputs.end())
            {
                result += "vec4 i_Position = vec4(i_Position3D, 1.0);\n";
            }

            if (it != VertexInputs.end() && it2 != VertexInputs.end())
            {
                PLS_LOG_ERROR("Both Position2D and Position3D are present");
                success = false;
                return "";
            }

            if (it == VertexInputs.end() && it2 == VertexInputs.end())
            {
                PLS_LOG_ERROR("Neither Position2D nor Position3D are present");
                success = false;
                return "";
            }

            if (it != VertexInputs.end())
            {
                VertexInputs.erase(it);
            }
            else
            {
                VertexInputs.erase(it2);
            }

            // Convert matrix columns to mat4
            for (const InputElement& input : VertexInputs)
            {
                if (input.Input.Type == InputUniformType::Matrix4)
                {
                    result += "mat4 i_" + input.Input.Name + " = mat4(i_" + input.Input.Name + "_C0, i_" + input.Input.Name + "_C1, i_" + input.Input.Name + "_C2, i_" + input.Input.Name + "_C3);\n";
                }
            }

            success = true;
            return result;
        }

        std::pair<std::string, std::string> GenerateVertexVaryings()
        {
            std::string result1;
            std::string result2;
            for (const InputElement& varying : VertexVaryings)
            {
                result1 += "out " + GetTypeString(varying.Input.Type) + " v_" + varying.Input.Name + ";\n";
                result2 += "v_" + varying.Input.Name + " = i_" + varying.Input.Name + ";\n";
            }
            
            return std::make_pair(result1, result2);
        }

        std::string GenerateFragmentInputs()
        {
            std::string result;
            for (const InputElement& input : VertexVaryings)
            {
                result += "in " + GetTypeString(input.Input.Type) + " v_" + input.Input.Name + ";\n";
            }

            return result;
        }

        std::string GenerateFragmentUniforms()
        {
            std::string result;
            for (const InputUniform& uniform : FragmentUniforms)
            {
                result += "uniform " + GetTypeString(uniform.Type) + " u_" + uniform.Name + ";\n";
            }

            return result;
        }

        std::string GetFragmentInputOrUniformName(std::string name, bool remove)
        {
            auto it = std::find_if(VertexVaryings.begin(), VertexVaryings.end(), [&name](const InputElement& element) { return element.Input.Name == name; });
            if (it != VertexVaryings.end())
            {
                if (remove)
                    VertexVaryings.erase(it);
                return "v_" + name;
            }

            auto it2 = std::find_if(FragmentUniforms.begin(), FragmentUniforms.end(), [&name](const InputUniform& uniform) { return uniform.Name == name; });
            if (it2 != FragmentUniforms.end())
            {
                if (remove)
                    FragmentUniforms.erase(it2);
                return "u_" + name;
            }

            return "";
        }
    };

    std::shared_ptr<Shader> CreateShaderWithSignature(const Shading::ShaderSignature& signature, const Shading::ShaderInputOrder& inputOrder)
    {
        // Check for overlap in input and uniform, return nullptr if there is overlap
        if ((signature.VertexInputs & signature.VertexUniforms) != 0 || (signature.FragmentInputs & signature.FragmentUniforms) != 0)
            return nullptr;

        static const std::array<InputUniform, 64> uniformMap = CreateUniformMap();
        std::vector<InputUniform> vertexInputsUnordered;
        std::vector<InputUniform> vertexVaryingsUnordered;
        ShaderIO io;

        for (std::uint32_t i = 0; i < 32; ++i)
        {
            if ((signature.VertexInputs & (1 << i)) != 0)
            {
                vertexInputsUnordered.push_back(uniformMap[i]);
            }
            if ((signature.VertexUniforms & (1 << i)) != 0)
            {
                io.VertexUniforms.push_back(uniformMap[i]);
            }
            if ((signature.FragmentInputs & (1 << i)) != 0)
            {
                vertexVaryingsUnordered.push_back(uniformMap[i]);
            }
            if ((signature.FragmentUniforms & (1 << i)) != 0)
            {
                io.FragmentUniforms.push_back(uniformMap[i]);
            }
        }

        // Try to order correctly
        std::uint16_t index = 0;
        for (std::size_t i = 0; i < inputOrder.VertexInputs.size(); ++i)
        {
            auto it = std::find_if(vertexInputsUnordered.begin(), vertexInputsUnordered.end(), [&inputOrder, i](const InputUniform& input) { return input.NumericalRepr == static_cast<std::uint32_t>(inputOrder.VertexInputs[i]); });
            if (it != vertexInputsUnordered.end())
            {
                io.VertexInputs.push_back({ *it, index++ });
                if (it->Type == InputUniformType::Matrix4)
                    index += 3; // Skip the next 3 indices (they are taken by the matrix columns)
                vertexInputsUnordered.erase(it);
                continue;
            }

            auto it2 = std::find_if(vertexVaryingsUnordered.begin(), vertexVaryingsUnordered.end(), [&inputOrder, i](const InputUniform& input) { return input.NumericalRepr == static_cast<std::uint32_t>(inputOrder.VertexInputs[i]); });
            if (it2 != vertexVaryingsUnordered.end())
            {
                io.VertexVaryings.push_back({ *it2, index++ });
                vertexVaryingsUnordered.erase(it2);
                continue;
            }
        }

        if (!vertexInputsUnordered.empty() || !vertexVaryingsUnordered.empty())
        {
            PLS_LOG_WARN("ShaderInputOrder did not contain all inputs");
            return nullptr;
        }

        bool success;
        std::string vertexShaderSource = "#version 330 core\n";
        vertexShaderSource += io.GenerateVertexInputs(success);
        if (!success)
            return nullptr;
        vertexShaderSource += io.GenerateVertexUniforms();
        auto [vertexVaryings, vertexVaryingsAssignments] = io.GenerateVertexVaryings();
        vertexShaderSource += vertexVaryings;
        vertexShaderSource += "void main()\n{\n";
        vertexShaderSource += io.GenerateConversions(success);

        if (!success)
            return nullptr;
        vertexShaderSource += vertexVaryingsAssignments;

        std::string modelMatrix = io.GetVertexInputOrUniformName("ModelMatrix", true);
        if (!modelMatrix.empty())
            vertexShaderSource += "i_Position = " + modelMatrix + " * i_Position;\n";
        std::string viewMatrix = io.GetVertexInputOrUniformName("ViewMatrix", true);
        if (!viewMatrix.empty())
            vertexShaderSource += "i_Position = " + viewMatrix + " * i_Position;\n";
        std::string projectionMatrix = io.GetVertexInputOrUniformName("ProjectionMatrix", true);
        if (!projectionMatrix.empty())
            vertexShaderSource += "i_Position = " + projectionMatrix + " * i_Position;\n";

        // TODO: Apply other inputs and uniforms to the position

        vertexShaderSource += "gl_Position = i_Position;\n";
        vertexShaderSource += "}\n";


        std::string fragmentShaderSource = "#version 330 core\n";
        fragmentShaderSource += io.GenerateFragmentInputs();
        fragmentShaderSource += io.GenerateFragmentUniforms();
        fragmentShaderSource += "out vec4 o_Color;\n";

        fragmentShaderSource += "void main()\n{\n";
        fragmentShaderSource += "o_Color = vec4(1.0, 1.0, 1.0, 1.0);\n";

        std::string texture2D = io.GetFragmentInputOrUniformName("Texture2D", true);
        if (!texture2D.empty())
        {
            std::string texCoord = io.GetFragmentInputOrUniformName("TextureCoord2D", true);
            if (texCoord.empty())
            {
                PLS_LOG_ERROR("Texture2D input was present, but TextureCoord2D was not");
                return nullptr;
            }

            fragmentShaderSource += "o_Color = o_Color * texture(" + texture2D + ", " + texCoord + ");\n";
        }

        // For all other inputs, apply them to the color
        
        for (const ShaderIO::InputElement& input : io.VertexVaryings)
        {
            std::string inputName = "v_" + input.Input.Name;
            if (input.Input.Type == InputUniformType::Sampler2D)
            {
                PLS_LOG_ERROR("Sampler2D uniform {} was present in fragment shader", input.Input.Name);
                return nullptr;
            }
            fragmentShaderSource += "o_Color = o_Color * " + inputName + ";\n";
        }

        for (const InputUniform& uniform : io.FragmentUniforms)
        {
            std::string uniformName = "u_" + uniform.Name;
            if (uniform.Type == InputUniformType::Sampler2D)
            {
                PLS_LOG_ERROR("Sampler2D uniform {} was present in fragment shader", uniform.Name);
                return nullptr;
            }
            fragmentShaderSource += "o_Color = o_Color * " + uniformName + ";\n";
        }

        fragmentShaderSource += "}\n";

        OpenGL::Shader vertexShader(OpenGL::ShaderType::VertexShader);
        vertexShader.ShaderSource(vertexShaderSource);

        if (!vertexShader.Compile())
        {
            PLS_LOG_ERROR("Failed to compile vertex shader: {}", vertexShader.GetInfoLog());
            return nullptr;
        }

        OpenGL::Shader fragmentShader(OpenGL::ShaderType::FragmentShader);
        fragmentShader.ShaderSource(fragmentShaderSource);

        if (!fragmentShader.Compile())
        {
            PLS_LOG_ERROR("Failed to compile fragment shader: {}", fragmentShader.GetInfoLog());
            return nullptr;
        }

        std::vector<OpenGL::Shader> shaders;
        shaders.push_back(std::move(vertexShader));
        shaders.push_back(std::move(fragmentShader));

        return std::make_shared<OpenGL::GLShader>(std::move(shaders), signature, inputOrder);
    }
}
