#include "Pulsarionpch.h"
#ifdef PLS_USE_GLFW_WINDOW
#include "GLFWWindow.h"

#include "Pulsarion/Event/Event.h"
#include "Pulsarion/Event/KeyEvent.h"
#include "Pulsarion/Event/MouseEvent.h"
#include "Pulsarion/Event/WindowEvent.h"


#include "GLFW/glfw3.h"

namespace Pulsarion
{
    class GLFW
    {
    public:
        static void Init()
        {
            if (s_Initialized)
                return;

            // Setup error callback to log errors if initialization fails
            glfwSetErrorCallback(GLFWErrorCallback);

            if (!glfwInit())
            {
                PLS_LOG_FATAL("Failed to initialize GLFW!");
                std::abort();
                return;
            }
        }

        static GLFWwindow* NewWindow(const WindowProperties& properties)
        {
            Init();

            GLFWwindow* window;

            if (s_GLVersionMajor == 0)
            {
                // Try to use the highest available version
                std::uint32_t versions[] = {
                    4, 3,
                    4, 1,
                    3, 3,
                };
                for (std::size_t i = 0; i < sizeof(versions) / sizeof(std::uint32_t); i += 2)
                {
                    window = RequestVersionForWindow(properties, versions[i], versions[i + 1]);

                    if (window != nullptr)
                        break;
                }

                if (s_GLVersionMajor == 0)
                {
                    PLS_LOG_FATAL("Could not request OpenGL version higher than 3.3!");
                    std::abort();
                }
            }
            else
            {
                window = RequestVersionForWindow(properties, s_GLVersionMajor, s_GLVersionMinor);
                if (window == nullptr)
                {
                    PLS_LOG_FATAL("Could not request OpenGL version {0}.{1}!", s_GLVersionMajor, s_GLVersionMinor);
                    std::abort();
                }
            }

            s_WindowCount += 1;
            return window;
        }

        static void Shutdown(GLFWwindow* window)
        {
            if (!s_Initialized)
                return;

            if (window == nullptr)
            {
                PLS_LOG_WARN("Tried to shutdown GLFW without a window!");
                return;
                
            }

            glfwDestroyWindow(window);

            if (--s_WindowCount != 0)
                return;

            glfwTerminate();
        }

    private:
        static void GLFWErrorCallback(int error, const char* description)
        {
            PLS_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
        }

        static GLFWwindow* RequestVersionForWindow(const WindowProperties& properties, std::uint32_t versionMajor, std::uint32_t versionMinor)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
            PLS_RUN_IF_DEBUG(glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE));
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

            GLFWwindow* window = glfwCreateWindow(properties.GetWidth(), properties.GetHeight(), properties.GetTitle().c_str(), nullptr, nullptr);

            if (window != nullptr)
            {
                s_GLVersionMajor = versionMajor;
                s_GLVersionMinor = versionMinor;
                glfwShowWindow(window);
                return window;
            }

            return nullptr;
        }

    private:
        static bool s_Initialized;
        static uint32_t s_WindowCount;
        static uint32_t s_GLVersionMajor;
        static uint32_t s_GLVersionMinor;
    };
    bool GLFW::s_Initialized = false;
    uint32_t GLFW::s_WindowCount = 0;
    uint32_t GLFW::s_GLVersionMajor = 0;
    uint32_t GLFW::s_GLVersionMinor = 0;

    std::unique_ptr<Window> CreateWindowPointer(const WindowProperties& windowProperties)
    {
        Log::Init();
        PLS_LOG_DEBUG("Creating Window with title: {0}", windowProperties.GetTitle());
        return std::make_unique<GLFWWindow>(windowProperties);
    }

    GLFWWindow::GLFWWindow(const WindowProperties& properties) : m_Data()
    {
        m_Data.Width = properties.GetWidth();
        m_Data.Height = properties.GetHeight();
        m_Data.Title = properties.GetTitle();
        m_Data.VSync = true;
        m_Data.EventCallback = DefaultEventCallback;
        m_Window = GLFW::NewWindow(properties);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
        SetupCallbacks();
    }

    GLFWWindow::~GLFWWindow()
    {
        GLFW::Shutdown(m_Window);
    }

    void GLFWWindow::Close()
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
    }

    bool GLFWWindow::IsOpen() const
    {
        return !glfwWindowShouldClose(m_Window);
    }

    void GLFWWindow::OnFrame() const
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    void GLFWWindow::SetEventCallback(const EventCallbackFunction& callback)
    {
        m_Data.EventCallback = callback;
    }

    bool GLFWWindow::IsVSync() const noexcept
    {
        return m_Data.VSync;
    }

    void GLFWWindow::SetVSync(bool vsync)
    {
        m_Data.VSync = vsync;
        glfwSwapInterval(vsync ? 1 : 0);
    }

    std::uint32_t GLFWWindow::GetWidth() const noexcept
    {
        return m_Data.Width;
    }

    std::uint32_t GLFWWindow::GetHeight() const noexcept
    {
        return m_Data.Height;
    }

    const std::string& GLFWWindow::GetTitle() const noexcept
    {
        return m_Data.Title;
    }

    void GLFWWindow::SetTitle(const std::string& title)
    {
        m_Data.Title = title;
        glfwSetWindowTitle(m_Window, title.c_str());
    }

    void GLFWWindow::DefaultEventCallback(const Event& event)
    {
        PLS_LOG_TRACE("Event Trigerred: {0}", event.ToString());
    }

    void GLFWWindow::SetupCallbacks()
    {
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int newWidth, int newHeight)
            {
                WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                data->Width = newWidth;
                data->Height = newHeight;

                WindowResizeEvent event(newWidth, newHeight);
                data->EventCallback(event);
            });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
            {
                WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                WindowCloseEvent event;
                data->EventCallback(event);
            });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                switch (action)
                {
                case GLFW_PRESS: {
                    KeyPressedEvent event(static_cast<KeyCode>(key), false);
                    data->EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyPressedEvent event(static_cast<KeyCode>(key), true);
                    data->EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyReleasedEvent event(static_cast<KeyCode>(key));
                    data->EventCallback(event);
                    break;
                }
                }
            });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

                switch (action)
                {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(static_cast<MouseCode>(button));
                    data->EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
                    data->EventCallback(event);
                    break;
                }
                }
            });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                MouseScrollEvent event((float)xOffset, (float)yOffset);
                data->EventCallback(event);
            });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
                MouseMovedEvent event((float)xPos, (float)yPos);
                data->EventCallback(event);
            });
    }
}
#endif
