#include "Pulsarionpch.h"
#include "Texture.h"

namespace Pulsarion
{
    Texture2D::Texture2D(const Image& imageFile) : m_Image(imageFile), m_Backend(Create2DTextureBackend(imageFile)) {

    }

    Texture2D::~Texture2D() {

    }

    void Texture2D::Bind(std::uint32_t textureSlot) const {
        m_Backend->Bind(textureSlot);
    }

    void Texture2D::Unbind() const {
        m_Backend->Unbind();
    }
}
