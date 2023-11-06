#pragma once

#include "Pulsarion/Core/PulsarionCore.h"
#include "Event.h"

#include <string>

namespace Pulsarion
{
    class PULSARION_API AppRenderEvent : public Event
    {
        EVENT_CLASS_TYPE(AppRender);
        virtual std::int32_t GetCategoryFlags() const override { return static_cast<std::int32_t>(EventCategory::Application); }

        std::string ToString() const override { return "AppRenderEvent"; }
    };
}
