#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

namespace Pulsarion
{
    /// <summary>
    /// Bits, from right to left, represent the following:
    /// 0 - Position2D
    /// 1 - Position3D
    /// 2 - TexCoord2D
    /// 3 - TexCoord3D
    /// 4 - Normals
    /// 5 - BiTangents
    /// 6 - 
    /// ------
    /// 32 - ModelMatrix
    /// 33 - ViewMatrix
    /// 34 - ProjectionMatrix
    /// 35 - DiffuseColor
    /// </summary>
    enum class ShaderSignatureBit : std::uint8_t
    {
        Position2D = 0,
        Position3D = 1,
        TexCoord2D = 2,
        TexCoord3D = 3,
        Normals = 4,
        BiTangents = 5,

        ModelMatrix = 32,
        ViewMatrix = 33,
        ProjectionMatrix = 34,
        Texture = 35,
        DiffuseColor = 36
    };
    struct ShaderSignature
    {
        std::uint64_t inputsBitmap;
        std::uint64_t uniformsBitmap;

        ShaderSignature() : inputsBitmap(0), uniformsBitmap(0) {}

        void EnableInput(ShaderSignatureBit bit)
        {
            inputsBitmap |= (1ULL << static_cast<std::uint8_t>(bit));
        }

        void EnableUniform(ShaderSignatureBit bit)
        {
            uniformsBitmap |= (1ULL << static_cast<std::uint8_t>(bit));
        }

        bool operator==(const ShaderSignature& other) const
        {
            return inputsBitmap == other.inputsBitmap && uniformsBitmap == other.uniformsBitmap;
        }

        ShaderSignature operator|(const ShaderSignature& other) const
        {
            ShaderSignature result;
            result.inputsBitmap = inputsBitmap | other.inputsBitmap;
            result.uniformsBitmap = uniformsBitmap | other.uniformsBitmap;
            return result;
        }
    };

    class Shader
    {
    public:
        virtual ~Shader() = default;
        virtual void SetUniform(const std::string& name, const glm::mat4& value) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetUniform(const std::string& name, std::int32_t value) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        const ShaderSignature& GetSignature() const { return m_Signature; }
    protected:
        ShaderSignature m_Signature;
    };

    extern PULSARION_API std::shared_ptr<Shader> CreateShaderWithSignature(const ShaderSignature& signature);
}

namespace std {
    template <>
    struct hash<Pulsarion::ShaderSignature> {
        size_t operator()(const Pulsarion::ShaderSignature& s) const {
            size_t h1 = std::hash<std::uint64_t>()(s.inputsBitmap);
            size_t h2 = std::hash<std::uint64_t>()(s.uniformsBitmap);

            return h1 ^ (h2 << 1); // Shift and combine
        }
    };
}
