#include "Pulsarionpch.h"
#include "Image.h"
#include "File.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Pulsarion
{
    Image::Image(const File& file, bool unload) : m_Data(nullptr), m_Width(0), m_Height(0), m_BytesPerColor(0), m_AbsolutePath(file.GetAbsolutePath().string())
    {
        Load(); // Load variables
        if (unload) // Unload if needed
            Unload();
    }

    Image::~Image()
    {
        Unload();
    }

    Image::Image(const Image& other) : m_Data(nullptr), m_Width(other.m_Width), m_Height(other.m_Height), m_BytesPerColor(other.m_BytesPerColor)
    {
        if (other.m_Data != nullptr)
        {
            m_Data = new unsigned char[GetSize()];
            std::copy(other.m_Data, other.m_Data + GetSize(), m_Data);
        }
    }

    Image::Image(Image&& other) noexcept : m_Data(other.m_Data), m_Width(other.m_Width), m_Height(other.m_Height), m_BytesPerColor(other.m_BytesPerColor)
    {
        other.m_Data = nullptr;
    }

    bool Image::Load() const
    {
        stbi_set_flip_vertically_on_load(1);
        int bpp;
        m_Data = stbi_load(m_AbsolutePath.c_str(), &m_Width, &m_Height, &bpp, 0);
        m_BytesPerColor = bpp / 4;
        return m_Data != nullptr;
    }

    void Image::Unload() const
    {
        stbi_image_free(m_Data);
        m_Data = nullptr;
    }

    const unsigned char* Image::GetData() const
    {
        if (!IsLoaded()) Load();
        return m_Data;
    }
}
