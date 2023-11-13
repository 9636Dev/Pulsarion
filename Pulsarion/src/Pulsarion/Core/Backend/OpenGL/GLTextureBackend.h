#pragma once

#include "Pulsarion/Core/Texture.h"
#include "Pulsarion/Util/Image.h"

#include "Texture.h"

namespace Pulsarion::OpenGL
{
    class GLTexture2DBackend : public Texture2DBackend
    {
    public:
        GLTexture2DBackend(const Image& textureImage);
        ~GLTexture2DBackend();

        virtual bool Bind(std::uint32_t textureSlot) const override;
        virtual void Unbind() const override;
        virtual void SetData(const Image& image) override;

    private:
        OpenGL::Texture m_Texture;
    };
}
