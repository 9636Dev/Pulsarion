#include "Pulsarionpch.h"
#include "Slider.h"

#include "WidgetInternal.h"

#include <imgui.h>

namespace Pulsarion::UI
{
    bool SliderScaleN(const std::string& text, void* data, const void* min, const void* max, const std::uint32_t dimension, const DataType dataType)
    {
        return ImGui::SliderScalarN(text.c_str(), GetImGuiDataType(dataType), data, dimension, min, max);
    }
}
