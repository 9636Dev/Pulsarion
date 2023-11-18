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
    /// 6 -
    /// ------
    /// 32 - ModelMatrix
    /// 33 - ViewMatrix
    /// 34 - ProjectionMatrix
    /// 35 - Texture
    /// 36 - DiffuseColor
    /// ------
    /// </summary>
    enum class PULSARION_API ShaderSignatureBit : std::uint8_t
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
    struct PULSARION_API ShaderSignature
    {
        std::uint64_t InputsBitmap;
        std::uint64_t UniformsBitmap;
        std::uint64_t UniformBlockBitmap;

        ShaderSignature() : InputsBitmap(0), UniformsBitmap(0), UniformBlockBitmap(0) {}

        void EnableInput(ShaderSignatureBit bit)
        {
            InputsBitmap |= (1ULL << static_cast<std::uint8_t>(bit));
        }

        void EnableUniform(ShaderSignatureBit bit)
        {
            UniformsBitmap |= (1ULL << static_cast<std::uint8_t>(bit));
        }

        void EnableUniformBlock(ShaderSignatureBit bit)
        {
            UniformBlockBitmap |= (1ULL << static_cast<std::uint8_t>(bit));
        }

        bool IsInputEnabled(ShaderSignatureBit bit) const
        {
            return (InputsBitmap & (1ULL << static_cast<std::uint8_t>(bit))) != 0;
        }

        bool IsUniformEnabled(ShaderSignatureBit bit) const
        {
            return (UniformsBitmap & (1ULL << static_cast<std::uint8_t>(bit))) != 0;
        }

        bool IsUniformBlockEnabled(ShaderSignatureBit bit) const
        {
            return (UniformBlockBitmap & (1ULL << static_cast<std::uint8_t>(bit))) != 0;
        }

        bool operator==(const ShaderSignature& other) const
        {
            return InputsBitmap == other.InputsBitmap && UniformsBitmap == other.UniformsBitmap;
        }

        ShaderSignature operator|(const ShaderSignature& other) const
        {
            ShaderSignature result;
            result.InputsBitmap = InputsBitmap | other.InputsBitmap;
            result.UniformsBitmap = UniformsBitmap | other.UniformsBitmap;
            result.UniformBlockBitmap = UniformBlockBitmap | other.UniformBlockBitmap;
            return result;
        }
    };

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
            size_t h1 = std::hash<std::uint64_t>()(s.InputsBitmap);
            size_t h2 = std::hash<std::uint64_t>()(s.UniformsBitmap);

            return h1 ^ (h2 << 1); // Shift and combine
        }
    };
}
