#include "Pulsarionpch.h"
#include "ColorPicker.h"

#include <imgui.h>

namespace Pulsarion::UI
{
    ColorPicker4::ColorPicker4(const std::string& label, const glm::vec4& color)
        : m_Label(label), m_Color(color), m_IsUpdated(false)
    {
    }

    void ColorPicker4::Render() const
    {
        m_IsUpdated = ImGui::ColorEdit4(m_Label.c_str(), glm::value_ptr(m_Color));
    }

    const glm::vec4& ColorPicker4::GetColor() const
    {
        return m_Color;
    }

    void ColorPicker4::SetColor(const glm::vec4& color)
    {
        m_Color = color;
    }

    bool ColorPicker4::IsUpdated() const
    {
        return m_IsUpdated;
    }
}
