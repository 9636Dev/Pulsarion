#pragma once
#ifdef PLS_USE_GLFW_WINDOW
#include "Pulsarion/Window.h"

#include <memory>
#include <string>

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
        GLFWWindow(const WindowProperties& windowProperties);
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

    private:
        void SetupCallbacks();
        static void DefaultEventCallback(const Event& event);

        GLFWwindow* m_Window;
        WindowData m_Data;
    };
}

#endif
