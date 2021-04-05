#pragma once

#include "Aquarius/Core/Application.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>


namespace Aquarius {
	
	namespace Gui {

        enum class ImguiStyle
        {
            DARK,
            LIGHT,
            CLASSIC
        };

        void Init();

        // Setup Platform/Renderer backends
        void AttachRenderer(GLFWwindow* window, const std::string& glslVersion);

        // Set the style as either classic, dark, or light
        void SetStyle(ImguiStyle style);

        // Begin the ImGUI frame
        void NewFrame();

        // End frame / Render all ImGUI draw data
        void Render();

        // Free all ImGUI resources 
        void Shutdown();

        // Display ImGUI Demo Window
        void ShowDemoWindow(bool* show);

	} // namespace Gui

} // namespace Aquarius
