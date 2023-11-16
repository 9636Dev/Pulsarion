#include "Pulsarionpch.h"
#include "GLTextureBackend.h"

namespace Pulsarion::OpenGL
{
    GLTexture2DBackend::GLTexture2DBackend(const Image& imageTexture) : m_Texture()
    {
        m_Texture.DefaultSettings();
        SetData(imageTexture);
        Unbind();
    }

    GLTexture2DBackend::~GLTexture2DBackend()
    {
    
    }

    void GLTexture2DBackend::SetData(const Image& imageTexture)
    {
        m_Texture.SetData(imageTexture);
    }

    bool GLTexture2DBackend::Bind(std::uint32_t textureSlot) const
    {
        // TODO: Add check if textureSlot is valid
        m_Texture.Bind(GetTextureUnit(textureSlot));
        return true;
    }

    void GLTexture2DBackend::Unbind() const
    {
        m_Texture.Unbind();
    }
}

namespace Pulsarion
{
    std::unique_ptr<Texture2DBackend> Create2DTextureBackend(const Image& image)
    {
        return std::make_unique<OpenGL::GLTexture2DBackend>(image);
    }
}
