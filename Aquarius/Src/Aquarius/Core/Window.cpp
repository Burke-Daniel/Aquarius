#include "Window.h"
#include "Log.h"
#include <assert.h>

namespace Aquarius {

    Window::Window(uint32_t width, uint32_t height, std::string &&name, bool vsync)
        : m_Width(width),
          m_Height(height),
          m_Name(std::move(name)),
          m_VsyncEnabled(vsync),
          m_Window(nullptr),
          m_Context(nullptr)
    {}

    Window::WindowPtr Window::Create(uint32_t width, uint32_t height, std::string &&name, bool vsync)
    {
        return std::make_unique<Window>(width, height, std::move(name));
    }

    void Window::Initialize()
    {
        // Set GLFW error callback
        glfwSetErrorCallback([](int error_code, const char* description)
                             {
                                 AQ_CORE_ERROR("GLFW Error Occurred:");
                                 AQ_CORE_ERROR(description);
                             });

        // Initialize GLFW
        int initSuccess = glfwInit();
        if (!initSuccess)
        {
            AQ_CORE_FATAL("Failed to initialize GLFW");
        }
        else
        {
            AQ_CORE_INFO("GLFW successfully initialized");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef PLATFORM_MAC
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif // PLATFORM_MAC

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), NULL, NULL);
        if (m_Window == nullptr)
        {
            glfwTerminate();
            AQ_CORE_FATAL("Failed to create a glfw window");
        }

        // Generate context
        m_Context = RenderingContext::Create(m_Window);
        m_Context->Initialize();

        glViewport(0, 0, m_Width, m_Height);
        setVsync(m_VsyncEnabled);

        // Register Window Callbacks here
    }

    uint32_t Window::getWidth() const
    {
        return m_Width;
    }

    uint32_t Window::getHeight() const
    {
        return m_Height;
    }

    const std::string& Window::getName() const
    {
        return m_Name;
    }

    bool Window::isVsyncEnabled() const
    {
        return m_VsyncEnabled;
    }

    void Window::OnUpdate()
    {
        m_Context->SwapBuffers();
        glfwPollEvents();
    }

    Window::~Window()
    {
        Deallocate();
    }

    void Window::Deallocate()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();

        AQ_CORE_INFO("Window destroyed and GLFW terminated");
    }

    void Window::setVsync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
            AQ_CORE_INFO("Vsync enabled");
        }
        else
        {
            glfwSwapInterval(0);
            AQ_CORE_INFO("Vsync disabled");
        }
        m_VsyncEnabled = enabled;
    }

} // namespace Aquarius
