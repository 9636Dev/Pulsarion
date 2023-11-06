#pragma once

#include <string>

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
    virtual EventType GetEventType() const override	{ return GetStaticType(); }\
    virtual const std::string GetName() const override { return #type; }

namespace Pulsarion
{
    enum class PULSARION_API EventType : std::int32_t
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class PULSARION_API EventCategory : std::int32_t
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
        Event() : m_Handled(false)
        {

        }
        virtual ~Event() = default;
        Event(const Event&) = delete;
        virtual Event& operator=(const Event&) = delete;
        Event(Event&&) = default;
        virtual Event& operator=(Event&&) = default;

        virtual EventType GetEventType() const = 0;
        virtual std::int32_t GetCategoryFlags() const = 0;
        virtual const std::string GetName() const = 0;
        virtual std::string ToString() const = 0;
    private:
        bool m_Handled;
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
            if (m_Event.GetEventType() == T::GetStaticType())
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
