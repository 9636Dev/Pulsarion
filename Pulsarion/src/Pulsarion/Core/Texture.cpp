#include "Pulsarionpch.h"
#include "Texture.h"

namespace Pulsarion
{
    Texture::Texture(const File& imageFile) : m_Image(imageFile) {

    }

    Texture::~Texture() {

    }

    const Image& Texture::getImage() const {
        return m_Image;
    }
}