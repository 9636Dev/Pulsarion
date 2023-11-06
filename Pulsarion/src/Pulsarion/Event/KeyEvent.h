#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "KeyCodes.h"
#include "Event.h"

namespace Pulsarion {

    class PULSARION_API KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }
        virtual std::int32_t GetCategoryFlags() const override { return static_cast<std::int32_t>(EventCategory::Input) | static_cast<std::int32_t>(EventCategory::Keyboard); }
        
    protected:
        KeyEvent(const KeyCode keycode)
            : m_KeyCode(keycode) {}

        KeyCode m_KeyCode;
    };

    class PULSARION_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const KeyCode p_Keycode, bool p_IsRepeat = false)
            : KeyEvent(p_Keycode), m_IsRepeat(p_IsRepeat) {}

        bool IsRepeat() const { return m_IsRepeat; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed);
    private:
        bool m_IsRepeat;
    };

    class PULSARION_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(const KeyCode p_Keycode)
            : KeyEvent(p_Keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent (Key: " << m_KeyCode << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);
    };

    class PULSARION_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(const KeyCode p_Keycode)
            : KeyEvent(p_Keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent (Key: " << m_KeyCode << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}
