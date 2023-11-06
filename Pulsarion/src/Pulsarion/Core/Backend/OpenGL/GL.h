#pragma once

#include <cstdint>

namespace Pulsarion::OpenGL
{
    using VertexArray_t = std::uint32_t;
    using Buffer_t = std::uint32_t;
    using Shader_t = std::uint32_t;
    using Program_t = std::uint32_t;
    using Texture_t = std::uint32_t;
    using sizei_t = std::int32_t;
    using sizeiptr_t = std::int64_t;

    struct GLVersion
    {
        std::uint32_t Major;
        std::uint32_t Minor;
    };

    class GL
    {
    public:
        static void Init();
        static void Terminate();
    };
}
