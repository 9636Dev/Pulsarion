#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Pulsarion/Util/Image.h"
#include "Pulsarion/Util/File.h"

namespace Pulsarion
{
    class Texture
    {
    public:
        Texture(const File& imageFile);
        ~Texture();

        const Image& GetImage() const { return m_Image; }
    private:
        Image m_Image;
    };
}