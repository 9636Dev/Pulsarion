#include "Pulsarionpch.h"
#include "Window.h"

#include "Widget.h"

#include <imgui.h>

namespace Pulsarion::UI
{
    Window::Window(const std::string& title) : m_Title(title), m_IsOpen(true), m_ShouldHaveCloseButton(false), m_Size(glm::vec2(0.0f, 0.0f)), m_Position(glm::vec2(0.0f, 0.0f)), m_Collapsed(false), m_Resizable(true), m_Moveable(true), m_ScrollBarVisible(true), m_AutoResize(true), m_SaveSettings(true), m_MenuBar(false), m_NoBackground(false), m_NoScrollWithMouse(false), m_BackgroundAlpha(0.8f)
    {

    }

    Window::~Window()
    {

    }

    void Window::AddWidget(std::shared_ptr<Widget> widget)
    {
        m_Widgets.push_back(widget);
    }

    bool Window::RemoveWidget(std::shared_ptr<Widget> widget)
    {
        for (auto it = m_Widgets.begin(); it != m_Widgets.end(); ++it)
        {
            if (*it == widget)
            {
                m_Widgets.erase(it);
                return true;
            }
        }
        return false;
    }

    void Window::Render() const
    {
        if (!m_IsOpen)
            return;

        if (m_Size.IsDirty())
        {
            if (m_Resizable)
            {
                ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, FLT_MAX));
                ImGui::SetNextWindowSize(ImVec2(m_Size.GetConst().x, m_Size.GetConst().y), ImGuiCond_Appearing);
            }
            else ImGui::SetNextWindowSize(ImVec2(m_Size.GetConst().x, m_Size.GetConst().y));
            m_Size.SetDirty(false);
        }

        if (m_Position.IsDirty())
        {
            ImGui::SetNextWindowPos(ImVec2(m_Position.GetConst().x, m_Position.GetConst().y));
            m_Position.SetDirty(false);
        }

        if (m_Collapsed.IsDirty())
        {
            ImGui::SetNextWindowCollapsed(m_Collapsed.GetConst());
            m_Collapsed.SetDirty(false);
        }

        ImGui::SetNextWindowBgAlpha(m_BackgroundAlpha);

        // Flags
        ImGuiWindowFlags flags = 0;
        if (!m_Resizable) flags |= ImGuiWindowFlags_NoResize;
        if (!m_Moveable) flags |= ImGuiWindowFlags_NoMove;
        if (!m_ScrollBarVisible) flags |= ImGuiWindowFlags_NoScrollbar;
        if (m_AutoResize && !m_Resizable) flags |= ImGuiWindowFlags_AlwaysAutoResize;
        if (!m_SaveSettings) flags |= ImGuiWindowFlags_NoSavedSettings;
        if (m_MenuBar) flags |= ImGuiWindowFlags_MenuBar;
        if (m_NoBackground) flags |= ImGuiWindowFlags_NoBackground;
        if (m_NoScrollWithMouse) flags |= ImGuiWindowFlags_NoScrollWithMouse;

        // Begin window
        ImGui::Begin(m_Title.c_str(), m_ShouldHaveCloseButton ? &m_IsOpen : nullptr, flags);

        for (auto& widget : m_Widgets)
        {
            widget->Render();
        }

        ImGui::End();
    }

    void Window::Open()
    {
        m_IsOpen = true;
    }

    void Window::Close()
    {
        m_IsOpen = false;
    }

    bool Window::IsOpen() const
    {
        return m_IsOpen;
    }

    bool Window::ShouldHaveCloseButton() const
    {
        return m_ShouldHaveCloseButton;
    }

    void Window::SetShouldHaveCloseButton(bool shouldHaveCloseButton)
    {
        m_ShouldHaveCloseButton = shouldHaveCloseButton;
    }

    const glm::vec2& Window::GetSize() const
    {
        return m_Size.GetConst();
    }

    void Window::SetSize(const glm::vec2& size)
    {
        m_Size.Set(size);
    }

    const glm::vec2& Window::GetPosition() const
    {
        return m_Position.GetConst();
    }

    void Window::SetPosition(const glm::vec2& position)
    {
        m_Position.Set(position);
    }

    bool Window::IsCollapsed() const
    {
        return m_Collapsed.GetConst();
    }

    void Window::SetCollapsed(bool collapsed)
    {
        m_Collapsed.Set(collapsed);
    }

    bool Window::IsResizable() const
    {
        return m_Resizable;
    }

    void Window::SetResizable(bool resizable)
    {
        m_Resizable = resizable;
    }

    bool Window::IsMoveable() const
    {
        return m_Moveable;
    }

    void Window::SetMoveable(bool moveable)
    {
        m_Moveable = moveable;
    }

    bool Window::IsScrollBarVisible() const
    {
        return m_ScrollBarVisible;
    }

    void Window::SetScrollBarVisible(bool scrollBarVisible)
    {
        m_ScrollBarVisible = scrollBarVisible;
    }

    bool Window::IsAutoResize() const
    {
        return m_AutoResize;
    }

    void Window::SetAutoResize(bool autoResize)
    {
        m_AutoResize = autoResize;
    }

    bool Window::ShouldSaveSettings() const
    {
        return m_SaveSettings;
    }

    void Window::SetSaveSettings(bool saveSettings)
    {
        m_SaveSettings = saveSettings;
    }

    bool Window::HasMenuBar() const
    {
        return m_MenuBar;
    }

    void Window::SetMenuBar(bool menuBar)
    {
        m_MenuBar = menuBar;
    }

    bool Window::HasBackground() const
    {
        return !m_NoBackground;
    }

    void Window::SetBackground(bool background)
    {
        m_NoBackground = !background;
    }

    bool Window::HasScrollWithMouse() const
    {
        return !m_NoScrollWithMouse;
    }

    void Window::SetScrollWithMouse(bool scrollWithMouse)
    {
        m_NoScrollWithMouse = !scrollWithMouse;
    }

    float Window::GetBackgroundAlpha() const
    {
        return m_BackgroundAlpha;
    }

    void Window::SetBackgroundAlpha(float backgroundAlpha)
    {
        m_BackgroundAlpha = backgroundAlpha;
    }
}
