#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

namespace Pulsarion
{
    namespace Shading
    {
        enum class ShaderInputUniform : std::uint32_t
        {
            Position2D = 1 << 0,
            Position3D = 1 << 1,
            TexCoord2D = 1 << 2,
            TexCoord3D = 1 << 3,
            Normal2D = 1 << 4,
            Normal3D = 1 << 5,
            Tangent2D = 1 << 6,
            Tangent3D = 1 << 7,
            Bitangent2D = 1 << 8,
            Bitangent3D = 1 << 9,
            ModelMatrix = 1 << 10,
            ViewMatrix = 1 << 11,
            ProjectionMatrix = 1 << 12,
            Texture2D = 1 << 13,
            DiffuseColor = 1 << 14,
        };

        struct PULSARION_API ShaderSignature
        {
            std::uint32_t VertexInputs;
            std::uint32_t VertexUniforms;
            std::uint32_t FragmentInputs;
            std::uint32_t FragmentUniforms;

            ShaderSignature() : VertexInputs(0), VertexUniforms(0), FragmentInputs(0), FragmentUniforms(0)
            {

            }

            void Clear()
            {
                VertexInputs = 0;
                VertexUniforms = 0;
                FragmentInputs = 0;
                FragmentUniforms = 0;
            }

            void AddVertexInput(ShaderInputUniform input)
            {
                VertexInputs |= static_cast<std::uint32_t>(input);
            }

            void AddVertexUniform(ShaderInputUniform input)
            {
                VertexUniforms |= static_cast<std::uint32_t>(input);
            }

            void AddFragmentInput(ShaderInputUniform input)
            {
                FragmentInputs |= static_cast<std::uint32_t>(input);
            }

            void AddFragmentUniform(ShaderInputUniform input)
            {
                FragmentUniforms |= static_cast<std::uint32_t>(input);
            }

            bool operator==(const ShaderSignature& other) const
            {
                return VertexInputs == other.VertexInputs && VertexUniforms == other.VertexUniforms && FragmentInputs == other.FragmentInputs && FragmentUniforms == other.FragmentUniforms;
            }

            bool VertexInputContains(ShaderInputUniform input) const
            {
                return (VertexInputs & static_cast<std::uint32_t>(input)) != 0;
            }

            bool VertexUniformContains(ShaderInputUniform input) const
            {
                return (VertexUniforms & static_cast<std::uint32_t>(input)) != 0;
            }

            bool FragmentInputContains(ShaderInputUniform input) const
            {
                return (FragmentInputs & static_cast<std::uint32_t>(input)) != 0;
            }

            bool FragmentUniformContains(ShaderInputUniform input) const
            {
                return (FragmentUniforms & static_cast<std::uint32_t>(input)) != 0;
            }

            ShaderSignature operator|(const ShaderSignature& other) const
            {
                ShaderSignature result;
                result.VertexInputs = VertexInputs | other.VertexInputs;
                result.VertexUniforms = VertexUniforms | other.VertexUniforms;
                result.FragmentInputs = FragmentInputs | other.FragmentInputs;
                result.FragmentUniforms = FragmentUniforms | other.FragmentUniforms;
                return result;
            }
        };

        struct PULSARION_API ShaderInputOrder
        {
            std::vector<Shading::ShaderInputUniform> VertexInputs;

            static ShaderInputOrder DefaultOrder(const ShaderSignature& signature)
            {
                ShaderInputOrder order;
                for (std::uint32_t i = 0; i < 15; ++i)
                {
                    ShaderInputUniform input = static_cast<ShaderInputUniform>(1 << i);
                    if ((signature.VertexInputs | signature.FragmentInputs) & (static_cast<std::uint32_t>(input)))
                    {
                        order.VertexInputs.push_back(input);
                    }
                }

                return order;
            }
        };
    }

    class PULSARION_API Shader
    {
    public:
        virtual ~Shader() = default;
        virtual void SetUniform(const std::string& name, const glm::mat4& value) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetUniform(const std::string& name, std::int32_t value) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        const Shading::ShaderSignature& GetSignature() const { return m_Signature; }
        const Shading::ShaderInputOrder& GetInputOrder() const { return m_InputOrder; }
    protected:
        Shader(const Shading::ShaderSignature& signature, const Shading::ShaderInputOrder& inputOrder) : m_Signature(signature), m_InputOrder(inputOrder)
        {

        }

        Shading::ShaderSignature m_Signature;
        Shading::ShaderInputOrder m_InputOrder;
    };

    extern PULSARION_API std::shared_ptr<Shader> CreateShaderWithSignature(const Shading::ShaderSignature& signature, const Shading::ShaderInputOrder& inputOrder);
}

namespace std {
    template <>
    struct hash<Pulsarion::Shading::ShaderSignature> {
        size_t operator()(const Pulsarion::Shading::ShaderSignature& s) const {
            // Generate hash for all members of the struct and combine them all
            return ((hash<std::uint32_t>()(s.VertexInputs) ^ (hash<std::uint32_t>()(s.VertexUniforms) << 1)) >> 1) ^ (hash<std::uint32_t>()(s.FragmentInputs) << 1) ^ (hash<std::uint32_t>()(s.FragmentUniforms) << 1);
        }
    };
}
