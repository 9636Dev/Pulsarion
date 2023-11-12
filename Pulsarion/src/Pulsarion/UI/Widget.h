#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include <imgui.h>

namespace Pulsarion::UI
{
    class PULSARION_API Widget
    {
    public:
        virtual ~Widget() = default;

        virtual void Render() const = 0;
    };

    template<typename T>
    constexpr ImGuiDataType GetImGuiDataType();

    template<>
    inline ImGuiDataType GetImGuiDataType<float>()
    {
        return ImGuiDataType_Float;
    }

    template<>
    inline ImGuiDataType GetImGuiDataType<double>()
    {
        return ImGuiDataType_Double;
    }

    template<>
    inline ImGuiDataType GetImGuiDataType<std::int8_t>()
    {
        return ImGuiDataType_S8;
    }

    template<>
    inline ImGuiDataType GetImGuiDataType<std::uint8_t>()
    {
        return ImGuiDataType_U8;
    }

    template<>
    inline ImGuiDataType GetImGuiDataType<std::int16_t>()
    {
        return ImGuiDataType_S16;
    }

    template<>
    inline ImGuiDataType GetImGuiDataType<std::uint16_t>()
    {
        return ImGuiDataType_U16;
    }

    template<>
    inline ImGuiDataType GetImGuiDataType<std::int32_t>()
    {
        return ImGuiDataType_S32;
    }

    template<>
    inline ImGuiDataType GetImGuiDataType<std::uint32_t>()
    {
        return ImGuiDataType_U32;
    }

    template<>
    inline ImGuiDataType GetImGuiDataType<std::int64_t>()
    {
        return ImGuiDataType_S64;
    }

    template<>
    inline ImGuiDataType GetImGuiDataType<std::uint64_t>()
    {
        return ImGuiDataType_U64;
    }
}
