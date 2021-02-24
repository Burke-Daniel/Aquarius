
#include "Application.h"
#include "Aquarius/Core/Log.h"

namespace Aquarius {

	Application* Application::s_application = nullptr;

	Application* Application::get() { return s_application; }

	Window* Application::getWindow() { return m_window.get(); }

	Application::Application(std::string&& windowName)
		: m_window(Window::Create(800, 600, std::move(windowName)))
	{
		s_application = this;

		Log::initLoggers();

		m_window->Initialize();

		AQ_CORE_INFO("Window Initialized Sucessfully");
	}

	void Application::run()
	{
		while (true)
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}
	}

} // namespace Aquarius

extern Aquarius::Application::ApplicationPtr createApplication();

int main(int argc, char* argv[])
{
	auto application = createApplication();

	application->run();

	return 0;
}
