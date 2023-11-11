#pragma once

#include "Pulsarion/Core/PulsarionCore.h"

#include <glm/vec4.hpp>

#include <memory>

namespace Pulsarion
{
    class PULSARION_API Renderer
    {
    public:
        virtual ~Renderer() = default;

        virtual void Clear() = 0;
        virtual void SetClearColor(glm::vec4 color) = 0;
    };

    extern PULSARION_API std::unique_ptr<Renderer> CreateRenderer();
}
