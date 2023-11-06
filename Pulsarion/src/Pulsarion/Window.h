#pragma once

#include <memory>
#include "Event/Event.h"

namespace Pulsarion
{

    class Window
    {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

        virtual ~Window() = default;
        Window(const Window&) = delete;
        virtual Window& operator=(const Window&) = delete;
        Window(Window&&) = default;
        virtual Window& operator=(Window&&) = default;

        virtual void Close() = 0;
        virtual bool IsOpen() const = 0;
        virtual void OnFrame() = 0;

    };

    extern std::unique_ptr<Window> CreateWindow();
}
