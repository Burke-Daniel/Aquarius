#pragma once

#include "Aquarius/Core/Utility.h"
#include "Aquarius/Core/Window.h"
#include "Aquarius/Events/EventHandler.h"

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

		void onEvent(Event& event);
	protected:
		Application(std::string&& windowName = "Application");
	private:
		static Application* s_Application;
		uniquePtr<Window> m_Window;
		EventHandler m_EventHandler;
    };

} // namespace Aquarius
