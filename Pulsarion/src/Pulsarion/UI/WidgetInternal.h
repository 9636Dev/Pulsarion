#pragma once

#include "Widget.h"

#include <imgui.h>

namespace Pulsarion::UI
{
    constexpr ImGuiDataType GetImGuiDataType(DataType type)
    {
        switch (type)
        {
            case DataType::Float:
                return ImGuiDataType_Float;
            case DataType::Double:
                return ImGuiDataType_Double;
            case DataType::Int32:
                return ImGuiDataType_S32;
            default:
                return ImGuiDataType_S32;
        }
    }
}
