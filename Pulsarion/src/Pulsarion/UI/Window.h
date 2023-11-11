#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include "Pulsarion/Util/Modifiable.h"

#include <memory>
#include <string>
#include <glm/vec2.hpp>

namespace Pulsarion::UI
{
    class Widget;

    class PULSARION_API Window
    {
    public:
        Window(const std::string& title);
        ~Window();

        void AddWidget(std::shared_ptr<Widget> widget);
        bool RemoveWidget(std::shared_ptr<Widget> widget);

        void Render() const;

        void Open();
        void Close();
        bool IsOpen() const;
        bool ShouldHaveCloseButton() const;
        void SetShouldHaveCloseButton(bool shouldHaveCloseButton);
        const glm::vec2& GetSize() const;
        void SetSize(const glm::vec2& size);
        const glm::vec2& GetPosition() const;
        void SetPosition(const glm::vec2& position);
        bool IsCollapsed() const;
        void SetCollapsed(bool collapsed);
        bool IsResizable() const;
        void SetResizable(bool resizable);
        bool IsMoveable() const;
        void SetMoveable(bool moveable);
        bool IsScrollBarVisible() const;
        void SetScrollBarVisible(bool scrollBarVisible);
        bool IsAutoResize() const;
        void SetAutoResize(bool autoResize);
        bool ShouldSaveSettings() const;
        void SetSaveSettings(bool saveSettings);
        bool HasMenuBar() const;
        void SetMenuBar(bool menuBar);
        bool HasBackground() const;
        void SetBackground(bool background);
        bool HasScrollWithMouse() const;
        void SetScrollWithMouse(bool scrollWithMouse);
        float GetBackgroundAlpha() const;
        void SetBackgroundAlpha(float backgroundAlpha);

    private:
        std::vector<std::shared_ptr<Widget>> m_Widgets;
        std::string m_Title;
        mutable bool m_IsOpen;
        bool m_ShouldHaveCloseButton;
        mutable Modifiable<glm::vec2> m_Size;
        mutable Modifiable<glm::vec2> m_Position;
        mutable Modifiable<bool> m_Collapsed;
        bool m_Resizable;
        bool m_Moveable;
        bool m_ScrollBarVisible;
        bool m_AutoResize;
        bool m_SaveSettings;
        bool m_MenuBar;
        bool m_NoBackground;
        bool m_NoScrollWithMouse;
        float m_BackgroundAlpha;
    };
}
