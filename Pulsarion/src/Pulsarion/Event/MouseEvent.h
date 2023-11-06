#pragma once

#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Event.h"
#include "MouseCodes.h"

namespace Pulsarion {
    class PULSARION_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(const float p_MouseX, const float p_MouseY) :
            m_MouseX(p_MouseX), m_mouseY(p_MouseY) {}

        float GetMouseX() const { return m_MouseX; }
        float GetMouseY() const { return m_mouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent (Pos: " << m_MouseX << ", " << m_mouseY << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);
        virtual std::int32_t GetCategoryFlags() const override { return (std::int32_t)EventCategory::Mouse | (std::int32_t)EventCategory::Input; }

    private:
        const float m_MouseX;
        const float m_mouseY;
    };

    class PULSARION_API MouseScrollEvent : public Event {
    public:
        MouseScrollEvent(const float p_OffsetX, const float p_OffsetY) :
            m_OffsetX(p_OffsetX), m_OffsetY(p_OffsetY) {}

        float GetOffsetX() const { return m_OffsetX; }
        float GetOffsetY() const { return m_OffsetY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrollEvent (Offset: " << m_OffsetX << ", " << m_OffsetY << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled);
        virtual std::int32_t GetCategoryFlags() const override { return (std::int32_t)EventCategory::Mouse | (std::int32_t)EventCategory::Input; }

    private:
        const float m_OffsetX;
        const float m_OffsetY;
    };

    class PULSARION_API MouseButtonEvent : public Event {
    public:
        MouseCode GetMouseButton() const { return m_Button; }

        virtual std::int32_t GetCategoryFlags() const override { return (std::int32_t)EventCategory::Mouse | (std::int32_t)EventCategory::Input | (std::int32_t)EventCategory::MouseButton; }
    protected:
        MouseButtonEvent(const MouseCode button)
            : m_Button(button) {}

        MouseCode m_Button;
    };

    class PULSARION_API MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(const MouseCode button)
            : MouseButtonEvent(button) {};

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent (Button: " << m_Button << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class PULSARION_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const MouseCode button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent (Button:" << m_Button << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}
