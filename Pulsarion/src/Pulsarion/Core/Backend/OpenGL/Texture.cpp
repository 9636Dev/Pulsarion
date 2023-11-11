#include "Pulsarionpch.h"
#include "Texture.h"

namespace Pulsarion::OpenGL
{
    Texture_t CreateTexture()
    {
        Texture_t texture;
        GL::GenTextures(1, &texture);
        return texture;
    }

    Texture::Texture() : m_Texture(CreateTexture()), m_TextureUnit(TextureUnit::Texture0)
    {
        
    }

    Texture::~Texture()
    {
        GL::DeleteTextures(1, &m_Texture);
    }

    void Texture::DefaultSettings()
    {
        Bind();
        MinFilter(TextureFilter::Linear);
        MagFilter(TextureFilter::Linear);
        WrapS(TextureWrap::Repeat);
        WrapT(TextureWrap::Repeat);
    }

    void Texture::SetData(const Image& image)
    {
        Bind();
        GL::TexImage2D(TextureTarget::Texture2D, 0, InternalFormat::RGBA, image.GetWidth(), image.GetHeight(), 0, PixelFormat::RGBA, PixelType::UnsignedByte, image.GetData());
    }

    void Texture::Bind() const
    {
        GL::ActiveTexture(m_TextureUnit);
        GL::BindTexture(TextureTarget::Texture2D, m_Texture);
    }

    void Texture::Unbind() const
    {
        GL::BindTexture(TextureTarget::Texture2D, 0);
    }

    void Texture::SetTextureUnit(TextureUnit unit)
    {
        m_TextureUnit = unit;
    }

    void Texture::MinFilter(TextureFilter filter)
    {
        Bind();
        GL::TexParameteri(TextureTarget::Texture2D, TextureParameter::TextureMinFilter, static_cast<std::int32_t>(filter));
    }

    void Texture::MagFilter(TextureFilter filter)
    {
        Bind();
        GL::TexParameteri(TextureTarget::Texture2D, TextureParameter::TextureMagFilter, static_cast<std::int32_t>(filter));
    }

    void Texture::WrapS(TextureWrap wrap)
    {
        Bind();
        GL::TexParameteri(TextureTarget::Texture2D, TextureParameter::TextureWrapS, static_cast<std::int32_t>(wrap));
    }

    void Texture::WrapT(TextureWrap wrap)
    {
        Bind();
        GL::TexParameteri(TextureTarget::Texture2D, TextureParameter::TextureWrapT, static_cast<std::int32_t>(wrap));
    }
}
