#pragma once
#include "Pulsarion/Core/PulsarionCore.h"
#ifdef PLS_USE_GLFW_WINDOW
#include "Pulsarion/Core/Window.h"

#include <memory>
#include <string>
#include <deque>

struct GLFWwindow;

namespace Pulsarion
{
    struct WindowData
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        bool VSync;
        Window::EventCallbackFunction EventCallback;
    };

    class GLFWWindow : public Window
    {
    public:
        explicit GLFWWindow(const WindowProperties& windowProperties);
        ~GLFWWindow() override;

        void Close() override;
        bool IsOpen() const override;
        void OnFrame() const override;

        void SetEventCallback(const EventCallbackFunction& callback) override;
        void SetVSync(bool enabled) override;
        bool IsVSync() const noexcept override;

        [[nodiscard]] std::uint32_t GetWidth() const noexcept override;
        [[nodiscard]] std::uint32_t GetHeight() const noexcept override;
        [[nodiscard]] const std::string& GetTitle() const noexcept override;
        void SetTitle(const std::string& title) override;

        [[nodiscard]] float GetAverageFrameTime() const override;
        [[nodiscard]] float GetAverageFps() const override;
        [[nodiscard]] std::size_t GetFrameTimeCount() const override;
        void SetFrameTimeCount(std::size_t count) override;

        void SetCursorMode(CursorMode mode) override;
        [[nodiscard]] CursorMode GetCursorMode() const override;

    private:
        void SetupCallbacks();
        static void DefaultEventCallback(const Event& event);

        GLFWwindow* m_Window;
        WindowData m_Data;
        mutable std::deque<std::uint64_t> m_FrameTimes;
        std::size_t m_FrameTimeCapacity;
    };
}

#endif
