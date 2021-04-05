#include "Input.h"
#include "Aquarius/Core/Application.h"

#include "imgui.h"


namespace Aquarius {

	namespace Input {

		KeyState getKeyState(KeyCode key)
		{
			auto window = Application::get()->getWindow();
			return static_cast<KeyState>(glfwGetKey(window->get(), static_cast<int>(key)));
		}

		MouseButtonState getMouseButtonState(MouseButtonCode button)
		{
			auto window = Application::get()->getWindow();
			return static_cast<MouseButtonState>(glfwGetMouseButton(window->get(), static_cast<int>(button)));
		}

		bool isKeyPressed(KeyCode key)
		{
			ImGuiIO& io = ImGui::GetIO();
			bool imguiConsumingKeyboard = io.WantCaptureKeyboard;

			return getKeyState(key) == KeyState::Pressed && !imguiConsumingKeyboard;
		}

		bool isMouseButtonPressed(MouseButtonCode button)
		{
			ImGuiIO& io = ImGui::GetIO();
			bool imguiConsumingMouse = io.WantCaptureMouse;

			return getMouseButtonState(button) == MouseButtonState::Pressed && imguiConsumingMouse;
		}

		MousePosition getMousePosition()
		{
			auto window = Application::get()->getWindow();
			MousePosition position;
			glfwGetCursorPos(window->get(), &position.x, &position.y);

			return position;
		}

	} // namespace Input

} // namespace Aquarius
