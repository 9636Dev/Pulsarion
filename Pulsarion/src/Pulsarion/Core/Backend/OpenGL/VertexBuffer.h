#pragma once

#include "GL.h"
#include "Enum.h"

namespace Pulsarion::OpenGL
{
    class VertexArray;

    class VertexBufferLayout
    {
    public:
        friend class VertexArray;
        struct Attribute
        {
            std::uint16_t Size;
            Type Type;
            bool Normalized;
            bool Instanced;
            // -1 means that the strjde is calculated automatically
            std::int32_t Stride;
            // -1 means that the offset is calculated automatically
            sizeiptr_t Offset;

            Attribute(std::uint16_t size, OpenGL::Type type, bool normalized, bool instanced = false, std::int32_t stride = -1, sizeiptr_t offset = -1)
            {
                Size = size;
                Type = type;
                Normalized = normalized;
                Instanced = instanced;
                Stride = stride;
                Offset = offset;
            }
        };

        VertexBufferLayout();
        ~VertexBufferLayout();

        inline void PushMat4(bool instanced = false, std::int32_t stride = -1, sizeiptr_t offset = -1)
        {
            Push<float>(4, false, instanced, stride, offset);
            Push<float>(4, false, instanced, stride, offset);
            Push<float>(4, false, instanced, stride, offset);
            Push<float>(4, false, instanced, stride, offset);
        }

        template<Util::GLType T>
        inline void Push(std::uint16_t size, bool normalized = false, bool instanced = false, std::int32_t stride = -1, sizeiptr_t offset = -1)
        {
            m_Attributes.emplace_back(size, GL::GetGLType<T>(), normalized, instanced, stride, offset == -1 ? m_Stride : offset);
            m_Stride += size * sizeof(T);
        }
        inline void Clear()
        {
            m_Attributes.clear();
            m_Stride = 0;
        }

        inline std::uint32_t GetStride() const { return m_Stride; }

    private:
        std::vector<Attribute> m_Attributes;
        std::uint32_t m_Stride;
    };

    class VertexBuffer {
    public:
        friend class VertexArray;
        VertexBuffer();
        ~VertexBuffer();

        void SetData(const void* data, std::uint32_t size, BufferUsage = BufferUsage::StaticDraw);
        void SetSubData(const void* data, std::uint32_t size, std::uint32_t offset);
    private:
        void Bind() const;
        void Unbind() const;

        Buffer_t m_Buffer;
    };
}
