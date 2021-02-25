#pragma once

#include "Aquarius/Core/Utility.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>


namespace Aquarius {

    // OpenGL Rendering Context
    class RenderingContext
    {
    public:
        RenderingContext(GLFWwindow* window);
        static uniquePtr<RenderingContext> Create(GLFWwindow* window);

        void Initialize();
        void SwapBuffers();

    private:
        GLFWwindow* m_Window;
    };
} // namespace Aquarius
