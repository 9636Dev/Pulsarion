#include "Pulsarionpch.h"
#include "VertexArray.h"

#include "VertexBuffer.h"

namespace Pulsarion::OpenGL
{
    VertexArray_t CreateVertexArray()
    {
        VertexArray_t vertexArray;
        GL::GenVertexArrays(1, &vertexArray);
        return vertexArray;
    }

    VertexArray::VertexArray() : m_VertexArray(CreateVertexArray())
    {
        Unbind();
    }

    VertexArray::~VertexArray()
    {
        GL::DeleteVertexArrays(1, &m_VertexArray);
    }

    void VertexArray::Bind() const
    {
        GL::BindVertexArray(m_VertexArray);
    }

    void VertexArray::Unbind() const
    {
        GL::BindVertexArray(0);
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
    {
        Bind();
        vb.Bind();

        // Sort attributes by index
        std::vector<std::pair<std::uint32_t, VertexBufferLayout::Attribute>> attributes = layout.m_Attributes;
        std::sort(attributes.begin(), attributes.end(), [](const std::pair<std::uint32_t, VertexBufferLayout::Attribute>& a, const std::pair<std::uint32_t, VertexBufferLayout::Attribute>& b) { return a.first < b.first; });

        std::ptrdiff_t offset = 0;
        for (const auto& [index, attribute] : attributes)
        {
            std::int32_t stride = attribute.Stride == -1 ? layout.m_Stride : attribute.Stride;
            const void* offsetPtr = attribute.Offset == -1 ? (const void*)offset : (const void*)attribute.Offset;

            GL::EnableVertexAttribArray(index);
            if (attribute.Type == Type::Double)
                GL::VertexAttribLPointer(index, attribute.Size, attribute.Type, stride, offsetPtr);
            else
                GL::VertexAttribPointer(index, attribute.Size, attribute.Type, attribute.Normalized, stride, offsetPtr);
            if (attribute.Instanced)
            {
                GL::VertexAttribDivisor(index, 1);
            }

            offset += attribute.Size * GL::GetSizeOfGLType(attribute.Type);
        }
    }
}
