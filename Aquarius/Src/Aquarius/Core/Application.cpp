#include "Application.h"
#include "Aquarius/Core/Input.h"
#include "Aquarius/Core/Log.h"

#include <chrono>


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

		AQ_CORE_INFO("Window Initialized Sucessfully");
	}

	void Application::run()
	{
		auto time = std::chrono::high_resolution_clock::now();
		while (!glfwWindowShouldClose(m_Window->get()))
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto timeDelta = now - time;
			time = now;
			for (const auto& layer : m_layerStack)
			{
				layer->onUpdate(std::chrono::duration_cast<std::chrono::microseconds>(timeDelta).count() / 1000.0);
			}
			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(uniquePtr<Layer> layer)
	{
		m_layerStack.push_back(std::move(layer));
		m_layerStack.back()->onCreation();
	}

} // namespace Aquarius

extern Aquarius::uniquePtr<Aquarius::Application> createApplication();

int main(int argc, char* argv[])
{
	auto application = createApplication();

	application->run();

	return 0;
}
