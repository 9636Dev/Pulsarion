#pragma once

#include <cstdint>

namespace Pulsarion::OpenGL
{
    enum class PULSARION_API PolygonFace : std::uint32_t
    {
        Front = 0x0404,
        Back = 0x0405,
        FrontAndBack = 0x0408
    };

    enum class PULSARION_API PolygonMode : std::uint32_t
    {
        Point = 0x1B00,
        Line = 0x1B01,
        Fill = 0x1B02
    };

    enum class PULSARION_API TextureWrap : std::uint32_t {
        REPEAT = 0x2901,
        MIRRORED_REPEAT = 0x8370,
        CLAMP_TO_EDGE = 0x812F,
        CLAMP_TO_BORDER = 0x812D
    };

    enum class PULSARION_API TextureUnit : std::uint32_t {
        TEXTURE0 = 0x84C0,
        TEXTURE1 = 0x84C1,
        TEXTURE2 = 0x84C2,
        TEXTURE3 = 0x84C3,
        TEXTURE4 = 0x84C4,
        TEXTURE5 = 0x84C5,
        TEXTURE6 = 0x84C6,
        TEXTURE7 = 0x84C7,
        TEXTURE8 = 0x84C8,
        TEXTURE9 = 0x84C9,
        TEXTURE10 = 0x84CA,
        TEXTURE11 = 0x84CB,
        TEXTURE12 = 0x84CC,
        TEXTURE13 = 0x84CD,
        TEXTURE14 = 0x84CE,
        TEXTURE15 = 0x84CF,
    };

    enum class PULSARION_API TextureFilter : std::uint32_t {
        NEAREST = 0x2600,
        LINEAR = 0x2601,
        NEAREST_MIPMAP_NEAREST = 0x2700,
        LINEAR_MIPMAP_NEAREST = 0x2701,
        NEAREST_MIPMAP_LINEAR = 0x2702,
        LINEAR_MIPMAP_LINEAR = 0x2703
    };

    enum class PULSARION_API GetParameterI : std::uint32_t {
        VERTEX_ARRAY_BINDING = 0x85B5,
        ARRAY_BUFFER_BINDING = 0x8894,
        ELEMENT_ARRAY_BUFFER_BINDING = 0x8895,
        MAX_VERTEX_ATTRIBS = 0x8869,
        CURRENT_PROGRAM = 0x8B8D,
        FRAMEBUFFER_BINDING = 0x8CA6,
        MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D,
    };

    enum class PULSARION_API DrawMode : std::uint32_t {
        POINTS = 0x0000,
        LINES = 0x0001,
        LINE_LOOP = 0x0002,
        LINE_STRIP = 0x0003,
        TRIANGLES = 0x0004,
        TRIANGLE_STRIP = 0x0005,
        TRIANGLE_FAN = 0x0006
    };

    enum class PULSARION_API TextureParameter : std::uint32_t
    {
        DEPTH_STENCIL_TEXTURE_MODE = 0x90EA,
        TEXTURE_BASE_LEVEL = 0x813C,
        TEXTURE_COMPARE_FUNC = 0x884D,
        TEXTURE_COMPARE_MODE = 0x884C,
        TEXTURE_LOD_BIAS = 0x8501,
        TEXTURE_MIN_FILTER = 0x2801,
        TEXTURE_MAG_FILTER = 0x2800,
        TEXTURE_MIN_LOD = 0x813A,
        TEXTURE_MAX_LOD = 0x813B,
        TEXTURE_MAX_LEVEL = 0x813D,
        TEXTURE_SWIZZLE_R = 0x8E42,
        TEXTURE_SWIZZLE_G = 0x8E43,
        TEXTURE_SWIZZLE_B = 0x8E44,
        TEXTURE_SWIZZLE_A = 0x8E45,
        TEXTURE_WRAP_S = 0x2802,
        TEXTURE_WRAP_T = 0x2803,
        TEXTURE_WRAP_R = 0x8072
    };

    enum class PULSARION_API InternalFormat : std::uint32_t
    {
        DEPTH_COMPONENT = 0x1902,
        DEPTH_STENCIL = 0x84F9,
        RED = 0x1903,
        RG = 0x8227,
        RGB = 0x1907,
        RGBA = 0x1908,
        R8 = 0x8229,
        R8_SNORM = 0x8F94,
        R16 = 0x822A,
        R16_SNORM = 0x8F98,
        RG8 = 0x822B,
        RG8_SNORM = 0x8F95,
        RG16 = 0x822C,
        RG16_SNORM = 0x8F99,
        R3_G3_B2 = 0x2A10,
        RGB4 = 0x804F,
        RGB5 = 0x8050,
        RGB8 = 0x8051,
        RGB8_SNORM = 0x8F96,
        RGB10 = 0x8052,
        RGB12 = 0x8053,
        RGB16_SNORM = 0x8F9A,
        RGBA2 = 0x8055,
        RGBA4 = 0x8056,
        RGB5_A1 = 0x8057,
        RGBA8 = 0x8058,
        RGBA8_SNORM = 0x8F97,
        RGB10_A2 = 0x8059,
        RGB10_A2UI = 0x906F,
        RGBA12 = 0x805A,
        RGBA16 = 0x805B,
        SRGB8 = 0x8C41,
        SRGB8_ALPHA8 = 0x8C43,
        R16F = 0x822D,
        RG16F = 0x822F,
        RGB16F = 0x881B,
        RGBA16F = 0x881A,
        R32F = 0x822E,
        RG32F = 0x8230
    };

    enum class PULSARION_API PixelFormat : std::uint32_t
    {
        DEPTH_COMPONENT = 0x1902,
        DEPTH_STENCIL = 0x84F9,
        RED = 0x1903,
        RG = 0x8227,
        RGB = 0x1907,
        RGBA = 0x1908,
        BGR = 0x80E0,
        BGRA = 0x80E1,
        RED_INTEGER = 0x8D94,
        RG_INTEGER = 0x8228,
        RGB_INTEGER = 0x8D98,
        RGBA_INTEGER = 0x8D99,
        BGR_INTEGER = 0x8D9A,
        BGRA_INTEGER = 0x8D9B,
        STENCIL_INDEX = 0x1901
    };

    enum class PULSARION_API PixelType : std::uint32_t
    {
        UNSIGNED_BYTE = 0x1401,
        BYTE = 0x1400,
        UNSIGNED_SHORT = 0x1403,
        SHORT = 0x1402,
        UNSIGNED_INT = 0x1405,
        INT = 0x1404,
        FLOAT = 0x1406,
        UNSIGNED_BYTE_3_3_2 = 0x8032,
        UNSIGNED_BYTE_2_3_3_REV = 0x8362,
        UNSIGNED_SHORT_5_6_5 = 0x8363,
        UNSIGNED_SHORT_5_6_5_REV = 0x8364,
        UNSIGNED_SHORT_4_4_4_4 = 0x8033,
        UNSIGNED_SHORT_4_4_4_4_REV = 0x8365,
        UNSIGNED_SHORT_5_5_5_1 = 0x8034,
        UNSIGNED_SHORT_1_5_5_5_REV = 0x8366,
        UNSIGNED_INT_8_8_8_8 = 0x8035,
        UNSIGNED_INT_8_8_8_8_REV = 0x8367,
        UNSIGNED_INT_10_10_10_2 = 0x8036,
        UNSIGNED_INT_2_10_10_10_REV = 0x8368
    };

    enum class PULSARION_API TextureTarget : std::uint32_t
    {
        TEXTURE_1D = 0x0DE0,
        TEXTURE_2D = 0x0DE1,
        TEXTURE_3D = 0x806F,
        TEXTURE_1D_ARRAY = 0x8C18,
        TEXTURE_2D_ARRAY = 0x8C1A,
        TEXTURE_RECTANGLE = 0x84F5,
        TEXTURE_CUBE_MAP = 0x8513,
        TEXTURE_CUBE_MAP_ARRAY = 0x9009,
        TEXTURE_BUFFER = 0x8C2A,
        TEXTURE_2D_MULTISAMPLE = 0x9100,
        TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9102
    };

    enum class PULSARION_API BufferTarget : std::uint32_t {
        ARRAY_BUFFER = 0x8892,
        ATOMIC_COUNTER_BUFFER = 0x92C0,
        COPY_READ_BUFFER = 0x8F36,
        COPY_WRITE_BUFFER = 0x8F37,
        DRAW_INDIRECT_BUFFER = 0x8F3F,
        DISPATCH_INDIRECT_BUFFER = 0x90EE,
        ELEMENT_ARRAY_BUFFER = 0x8893,
        PIXEL_PACK_BUFFER = 0x88EB,
        PIXEL_UNPACK_BUFFER = 0x88EC,
        QUERY_BUFFER = 0x9192,
        SHADER_STORAGE_BUFFER = 0x90D2,
        TEXTURE_BUFFER = 0x8C2A,
        TRANSFORM_FEEDBACK_BUFFER = 0x8C8E,
        UNIFORM_BUFFER = 0x8A11
    };

    enum class PULSARION_API BufferUsage : std::uint32_t {
        STREAM_DRAW = 0x88E0,
        STREAM_READ = 0x88E1,
        STREAM_COPY = 0x88E2,
        STATIC_DRAW = 0x88E4,
        STATIC_READ = 0x88E5,
        STATIC_COPY = 0x88E6,
        DYNAMIC_DRAW = 0x88E8,
        DYNAMIC_READ = 0x88E9,
        DYNAMIC_COPY = 0x88EA
    };

    enum class PULSARION_API ShaderType : std::uint32_t {
        VERTEX_SHADER = 0x8B31,
        FRAGMENT_SHADER = 0x8B30,
        GEOMETRY_SHADER = 0x8DD9,
        TESS_CONTROL_SHADER = 0x8E88,
        TESS_EVALUATION_SHADER = 0x8E87,
        COMPUTE_SHADER = 0x91B9
    };

    enum class PULSARION_API GLType : std::uint32_t {
        BYTE = 0x1400,
        UNSIGNED_BYTE = 0x1401,
        SHORT = 0x1402,
        UNSIGNED_SHORT = 0x1403,
        INT = 0x1404,
        UNSIGNED_INT = 0x1405,
        FLOAT = 0x1406,
        FIXED = 0x140C,
        DOUBLE = 0x140A,
        HALF_FLOAT = 0x140B
    };

    enum class PULSARION_API ShaderParameter : std::uint32_t {
        DELETE_STATUS = 0x8B80,
        COMPILE_STATUS = 0x8B81,
        INFO_LOG_LENGTH = 0x8B84,
        SHADER_SOURCE_LENGTH = 0x8B88
    };

    enum class PULSARION_API ProgramParameter : std::uint32_t {
        DELETE_STATUS = 0x8B80,
        LINK_STATUS = 0x8B82,
        VALIDATE_STATUS = 0x8B83,
        INFO_LOG_LENGTH = 0x8B84,
        ATTACHED_SHADERS = 0x8B85,
        ACTIVE_ATTRIBUTES = 0x8B89,
        ACTIVE_ATTRIBUTE_MAX_LENGTH = 0x8B8A,
        ACTIVE_UNIFORMS = 0x8B86
    };

    enum class PULSARION_API ClearTarget : std::uint32_t {
        COLOR_BUFFER_BIT = 0x00004000,
        DEPTH_BUFFER_BIT = 0x00000100,
        STENCIL_BUFFER_BIT = 0x00000400,

        COLOR_AND_DEPTH_BUFFER_BIT = 0x00004000 | 0x00000100,
        COLOR_AND_STENCIL_BUFFER_BIT = 0x00004000 | 0x00000400,
        DEPTH_AND_STENCIL_BUFFER_BIT = 0x00000100 | 0x00000400,
        COLOR_DEPTH_AND_STENCIL_BUFFER_BIT = 0x00004000 | 0x00000100 | 0x00000400,
    };
}
