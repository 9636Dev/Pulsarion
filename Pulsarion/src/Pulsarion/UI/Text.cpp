#include "Pulsarionpch.h"
#include "Text.h"

#include <imgui.h>

namespace Pulsarion::UI
{
    Text::Text(const std::string& text) : m_Text(text), m_Color(1.0f, 1.0f, 1.0f, 1.0f)
    {

    }

    Text::~Text()
    {

    }

    void Text::SetText(const std::string& text)
    {
        m_Text = text;
    }

    const std::string& Text::GetText() const
    {
        return m_Text;
    }

    void Text::SetColor(const glm::vec4& color)
    {
        m_Color = color;
    }

    const glm::vec4& Text::GetColor() const
    {
        return m_Color;
    }

    void Text::Render() const
    {
        ImGui::TextColored(ImVec4(m_Color.r, m_Color.g, m_Color.b, m_Color.a), m_Text.c_str());
    }
}
