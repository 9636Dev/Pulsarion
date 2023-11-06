#pragma once

#include <string>

namespace Pulsarion
{
    enum class PULSARION_API EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class PULSARION_API EventCategory
    {
        None = 0,
        Application = 1 << 0,
        Input = 1 << 1,
        Keyboard = 1 << 2,
        Mouse = 1 << 3,
        MouseButton = 1 << 4
    };

    class PULSARION_API Event
    {
        friend class EventDispatcher;

    public:
        virtual ~Event() = default;
        Event(const Event&) = delete;
        virtual Event& operator=(const Event&) = delete;
        Event(Event&&) = default;
        virtual Event& operator=(Event&&) = default;

        virtual EventType GetType() const = 0;
        virtual EventCategory GetCategory() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const = 0;

        virtual bool IsInCategory(EventCategory category) const = 0;
        virtual bool IsHandled() const = 0;

        virtual operator bool() const = 0;
    private:
        bool m_Handled = false;
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& p_Event) :
            m_Event(p_Event)
        {

        }

        // F is derived by the compiler
        template <typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetType() == T::GetStaticType())
            {
                m_Event.m_Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

        bool IsHandled() {
            return m_Event.m_Handled;
        }

    private:
        Event& m_Event;
    };
}
