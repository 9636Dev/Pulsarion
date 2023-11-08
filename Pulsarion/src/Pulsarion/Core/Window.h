#pragma once

#include <memory>
#include <functional>
#include <string>

#include "Pulsarion/Core/PulsarionCore.h"
#include "Event/Event.h"

namespace Pulsarion
{
    enum class PULSARION_API CursorMode
    {
        Normal = 0,
        Hidden = 1,
        Disabled = 2
    };

    class PULSARION_API WindowProperties
    {
    public:
        WindowProperties(std::uint32_t width = 1280, std::uint32_t height = 720, const std::string& title = "Pulsarion Window") noexcept
            : m_Width(width), m_Height(height), m_Title(title)
        {

        }

        [[nodiscard]] std::uint32_t GetWidth() const noexcept { return m_Width; }
        [[nodiscard]] std::uint32_t GetHeight() const noexcept { return m_Height; }
        [[nodiscard]] const std::string& GetTitle() const noexcept { return m_Title; }

     private:
        std::uint32_t m_Width;
        std::uint32_t m_Height;
        std::string m_Title;
    };


    class PULSARION_API Window
    {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

        Window() = default;
        virtual ~Window() = default;
        Window(const Window&) = delete;
        virtual Window& operator=(const Window&) = delete;
        Window(Window&&) = default;
        virtual Window& operator=(Window&&) = default;

        virtual void Close() = 0;
        virtual bool IsOpen() const = 0;
        virtual void OnFrame() const = 0;

        virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const noexcept = 0;

        [[nodiscard]] virtual std::uint32_t GetWidth() const noexcept = 0;
        [[nodiscard]] virtual std::uint32_t GetHeight() const noexcept = 0;
        [[nodiscard]] virtual const std::string& GetTitle() const noexcept = 0;
        virtual void SetTitle(const std::string& title) = 0;

        virtual float GetAverageFrameTime() const = 0;
        virtual float GetAverageFps() const = 0;
        [[nodiscard]] virtual std::size_t GetFrameTimeCount() const = 0;
        virtual void SetFrameTimeCount(std::size_t count) = 0;

        virtual void SetCursorMode(CursorMode mode) = 0;
        [[nodiscard]] virtual CursorMode GetCursorMode() const = 0;

    };

    extern PULSARION_API std::unique_ptr<Window> CreateWindowPointer(const WindowProperties& windowProperties);
}
