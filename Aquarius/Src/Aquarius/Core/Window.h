#pragma once
#include <string>
#include <memory>
#include <Aquarius/Renderer/RenderingContext.h>
#include <GLFW/glfw3.h>

namespace Aquarius {

    // GLFW Window
    class Window
    {
        using WindowPtr = std::unique_ptr<Window>;

    public:
        // Creation
        Window(uint32_t width, uint32_t height, std::string&& name, bool vsync = false);
        static WindowPtr Create(uint32_t width, uint32_t height, std::string&& name, bool vsync = false);

        // Initialize GLFW
        void Initialize();

        // Poll inputs and swap buffers
        void OnUpdate();

        // Utility methods
        uint32_t getWidth() const;
        uint32_t getHeight() const;
        const std::string& getName() const;
        bool getVsync() const;
        void setVsync(bool enabled);

        // Destruction
        ~Window();

    private:
        uint32_t m_Width;
        uint32_t m_Height;
        const std::string m_Name;
        bool m_VsyncEnabled;
        GLFWwindow* m_Window;
        std::unique_ptr<RenderingContext> m_Context;

        // Deallocate window resources
        void Deallocate();
    };
} // namespace Aquarius