#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Util/UsageType.h"

#include <optional>
#include <string>
#include <glm/vec4.hpp>

namespace Pulsarion
{
    class PULSARION_API Material
    {
    public:
        Material(UsageType type = UsageType::Static);
        ~Material();

        void SetTextureId(std::uint32_t textureId);
        void SetDiffuseColor(const glm::vec4& diffuseColor);
        void SetIsTransparent(bool isTransparent);

        std::optional<std::uint32_t> GetTextureId() const;
        const glm::vec4& GetDiffuseColor() const;
        bool GetIsTransparent() const;
        UsageType GetUsageType() const;

    private:
        UsageType m_UsageType;
        std::optional<std::uint32_t> m_TextureId;
        glm::vec4 m_DiffuseColor;
        bool m_IsTransparent;
    };
}
