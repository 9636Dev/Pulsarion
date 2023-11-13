#include "Pulsarionpch.h"
#include "Material.h"

namespace Pulsarion
{
    Material::Material(UsageType type) : m_TextureId(), m_DiffuseColor(1.0f, 1.0f, 1.0f, 1.0f), m_IsTransparent(false), m_UsageType(type)
    {

    }

    Material::~Material()
    {

    }

    void Material::SetTextureId(std::uint32_t textureId)
    {
        m_TextureId = textureId;
    }

    void Material::SetDiffuseColor(const glm::vec4& diffuseColor)
    {
        m_DiffuseColor = diffuseColor;
    }

    void Material::SetIsTransparent(bool isTransparent)
    {
        m_IsTransparent = isTransparent;
    }

    std::optional<std::uint32_t> Material::GetTextureId() const
    {
        return m_TextureId;
    }

    const glm::vec4& Material::GetDiffuseColor() const
    {
        return m_DiffuseColor;
    }

    bool Material::GetIsTransparent() const
    {
        return m_IsTransparent;
    }

    UsageType Material::GetUsageType() const
    {
        return m_UsageType;
    }
}
