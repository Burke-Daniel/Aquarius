#include "GuiManager.h"


namespace Aquarius {

    namespace Gui {

        void Init()
        {
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();

            // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        }

        // Setup Platform/Renderer backends
        void AttachRenderer(GLFWwindow* window, const std::string& glslVersion)
        {
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init(glslVersion.c_str());
        }

        // Set the style as either classic, dark, or light
        void SetStyle(ImguiStyle style)
        {
            switch (style)
            {
            case ImguiStyle::DARK:
                ImGui::StyleColorsDark();
                break;
            case ImguiStyle::LIGHT:
                ImGui::StyleColorsLight();
                break;
            case ImguiStyle::CLASSIC:
                ImGui::StyleColorsClassic();
                break;
            default:
                ImGui::StyleColorsDark();
            }
        }

        // Begin the ImGUI frame
        void NewFrame()
        {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        // End frame / Render all ImGUI draw data
        void Render()
        {
            ImGuiIO& io = ImGui::GetIO();

            // Set the ImGUI display size to the current window width and height
            Application* app = Application::get();
            io.DisplaySize = ImVec2(app->getWindow()->getWidth(), app->getWindow()->getHeight());

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        // Free all ImGUI resources 
        void Shutdown()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        // Display ImGUI Demo Window
        void ShowDemoWindow(bool* show)
        {
            ImGui::ShowDemoWindow(show);
        }

    } // namespace Gui

} // namespace Aquarius
