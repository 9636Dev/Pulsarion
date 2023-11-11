#pragma once

#include "GL.h"

namespace Pulsarion::OpenGL {

    class VertexBuffer;
    class VertexBufferLayout;

    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    private:
        VertexArray_t m_VertexArray;
    };
}
