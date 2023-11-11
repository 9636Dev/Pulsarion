#pragma once

#include "File.h"

namespace Pulsarion
{
    class Image
    {
    public:
        Image(const File& file, bool unload = true);
        ~Image();
        Image(const Image& other);
        Image(Image&& other) noexcept;

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }
        inline int GetBytesPerColor() const { return m_BytesPerColor; }
        inline int GetBytesPerPixel() const { return m_BytesPerColor * 4; }
        inline std::size_t GetSize() const { return static_cast<std::size_t>(m_Width) * m_Height * GetBytesPerPixel(); }

        inline bool IsLoaded() const { return m_Data != nullptr; }
        bool Load() const;
        void Unload() const;

        const unsigned char* GetData() const;
    private:
        std::string m_AbsolutePath;
        mutable unsigned char* m_Data;
        mutable int m_Width, m_Height, m_BytesPerColor;
    };
}
