#pragma once

#include "Aquarius/Core/Window.h"

#include <memory>

namespace Aquarius {

	class Application
	{
	public:
		using ApplicationPtr = std::unique_ptr<Application>;

		Application() = delete;
		Application(const Application&) = delete;

		virtual ~Application() {};

		static Application* get();

		Window* getWindow();

		void run();
	protected:
		Application(std::string&& windowName = "Application");
	private:
		static Application* s_Application;
		Window::WindowPtr m_Window;
	};

} // namespace Aquarius
