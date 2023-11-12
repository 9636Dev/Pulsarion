#include "Pulsarionpch.h"
#include "Button.h"

#include <imgui.h>

namespace Pulsarion::UI
{
    Button::Button(const std::string& text)
        : m_Text(text), m_Pressed(false)
    {

    }

    Button::~Button()
    {

    }

    void Button::Render() const
    {
        m_Pressed = ImGui::Button(m_Text.c_str());
    }

    void Button::SetText(const std::string& text)
    {
        m_Text = text;
    }

    const std::string& Button::GetText() const
    {
        return m_Text;
    }

    bool Button::IsPressed() const
    {
        return m_Pressed;
    }
}
