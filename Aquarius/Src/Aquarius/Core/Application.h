#pragma once

#include "Aquarius/Core/Window.h"
#include "Aquarius/Core/Utility.h"

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
		uniquePtr<Window> m_Window;
	};

} // namespace Aquarius
