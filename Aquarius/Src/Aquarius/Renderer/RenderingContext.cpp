#include "RenderingContext.h"
#include <Aquarius/Core/Log.h>


namespace Aquarius {

    RenderingContext::RenderingContext(GLFWwindow* window)
    :   m_Window(window)
    {}

    uniquePtr<RenderingContext> RenderingContext::Create(GLFWwindow *window)
    {
        return std::make_unique<RenderingContext>(window);
    }

    void RenderingContext::Initialize()
    {
        // Use GLAD to load opengl function pointers
        glfwMakeContextCurrent(m_Window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            AQ_CORE_FATAL("Failed to initialize GLAD" );
        }
        else
        {
            AQ_CORE_INFO("GLAD successfully initialized");
        }

        AQ_CORE_INFO("Vendor: %v", glGetString(GL_VENDOR));
        AQ_CORE_INFO("GPU: %v", glGetString(GL_RENDERER));
        AQ_CORE_INFO("OpenGL Version: %v", glGetString(GL_VERSION));
    }

    void RenderingContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }
} // namespace Aquarius
