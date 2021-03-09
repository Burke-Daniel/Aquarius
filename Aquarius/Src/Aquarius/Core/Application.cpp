#include "Application.h"
#include "Aquarius/Core/Input.h"
#include "Aquarius/Core/Log.h"
#include "Aquarius/Events/EventHandler.h"
#include "Aquarius/Events/KeyboardEvent.h"
#include "Aquarius/Events/MouseEvent.h"

namespace Aquarius {

	Application* Application::s_Application = nullptr;

	Application* Application::get() { return s_Application; }

	Window* Application::getWindow() { return m_Window.get(); }

	Application::Application(std::string&& windowName)
		: m_Window(Window::Create(800, 600, std::move(windowName)))
	{
		s_Application = this;

		Log::initLoggers();
		m_Window->Initialize();

		AQ_CORE_INFO("Window Initialized Successfully");
	}

	void Application::run()
	{
		while (!glfwWindowShouldClose(m_Window->get()))
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::onEvent(Event &event)
	{
	    EventHandler handler(event);
	}

} // namespace Aquarius

extern Aquarius::uniquePtr<Aquarius::Application> createApplication();

int main(int argc, char* argv[])
{
	auto application = createApplication();

	application->run();

	return 0;
}
