#pragma once

#include "Aquarius/Core/Window.h"

#include <memory>

namespace Aquarius {

	class Application
	{
	public:
		Application() = delete;
		Application(const Application&) = delete;

		using ApplicationPtr = std::unique_ptr<Application>;

		virtual ~Application() {};

		static Application* get();

		Window* getWindow();

		void run();
	protected:
		Application(std::string&& windowName = "Application");
	private:
		static Application* s_application;
		Window::WindowPtr m_window;
	};

} // namespace Aquarius
