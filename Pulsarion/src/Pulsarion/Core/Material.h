#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Util/UsageType.h"

#include <optional>
#include <string>
#include <glm/vec4.hpp>

namespace Pulsarion
{
    namespace Shading
    {
        struct ShaderSignature;
    }
    class PULSARION_API Material
    {
    public:
        Material(UsageType type = UsageType::Static);
        ~Material();

        void SetTextureId(std::uint32_t textureId);
        void SetDiffuseColor(const glm::vec4& diffuseColor);
        void SetIsTransparent(bool isTransparent);

        std::uint32_t GetTextureId() const;
        const glm::vec4& GetDiffuseColor() const;
        bool GetIsTransparent() const;
        UsageType GetUsageType() const;

        static Shading::ShaderSignature GetShaderSignature();

    private:
        UsageType m_UsageType;
        std::uint32_t m_TextureId;
        glm::vec4 m_DiffuseColor;
        bool m_IsTransparent;
    };
}
