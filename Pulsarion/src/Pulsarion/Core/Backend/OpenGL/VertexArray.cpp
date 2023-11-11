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

        for (std::uint32_t i = 0; i < layout.m_Attributes.size(); i++)
        {
            const auto& attribute = layout.m_Attributes[i];
            std::int32_t stride = attribute.Stride == -1 ? layout.m_Stride : attribute.Stride;
            GL::EnableVertexAttribArray(i);
            GL::VertexAttribPointer(i, attribute.Size, attribute.Type, attribute.Normalized, stride, (const void*)attribute.Offset);
            if (attribute.Instanced)
            {
                GL::VertexAttribDivisor(i, 1);
            }
        }
    }
}
