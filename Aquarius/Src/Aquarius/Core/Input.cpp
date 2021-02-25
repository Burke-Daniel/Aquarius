#include "Input.h"
#include "Application.h"


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
			return getKeyState(key) == KeyState::Pressed;
		}

		bool isMouseButtonPressed(MouseButtonCode button)
		{
			return getMouseButtonState(button) == MouseButtonState::Pressed;
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
