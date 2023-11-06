#pragma once
#include "Pulsarion/Core/PulsarionCore.h"
#include "Event.h"

#include <sstream>

namespace Pulsarion {

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int p_Width, unsigned int p_Height)
            : m_Width(p_Width), m_Height(p_Height) {}

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent (" << m_Width << ", " << m_Height << ")";
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        virtual std::int32_t GetCategoryFlags() const override { return static_cast<std::int32_t>(EventCategory::Application); }
    private:
        unsigned int m_Width, m_Height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        inline std::string ToString() const override { return "WindowCloseEvent"; }

        EVENT_CLASS_TYPE(WindowClose)
        virtual std::int32_t GetCategoryFlags() const override { return static_cast<std::int32_t>(EventCategory::Application); }
    };
}
