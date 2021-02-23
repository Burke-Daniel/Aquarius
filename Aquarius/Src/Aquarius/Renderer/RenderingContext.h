#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace Aquarius {

    // OpenGL Rendering Context
    class RenderingContext
    {
        using ContextPtr = std::unique_ptr<RenderingContext>;
    public:
        RenderingContext(GLFWwindow* window);
        static ContextPtr Create(GLFWwindow* window);

        void Initialize();
        void SwapBuffers();

        void Deallocate();
        ~RenderingContext();

    private:
        GLFWwindow* m_Window;
    };
} // namespace Aquarius
