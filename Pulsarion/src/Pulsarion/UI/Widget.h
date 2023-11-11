#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

namespace Pulsarion::UI
{
    class Widget
    {
    public:
        virtual ~Widget() = default;

        virtual void Render() const = 0;
    };
}
