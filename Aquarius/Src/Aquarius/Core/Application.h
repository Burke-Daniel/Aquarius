#pragma once

#include "Aquarius/Core/Layer.h"
#include "Aquarius/Core/Utility.h"
#include "Aquarius/Core/Window.h"
#include "Aquarius/Events/EventHandler.h"
#include "Aquarius/Sound/Devices.h"

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

		EventHandler& getEventHandler();

		void run();

		void onEvent(Event& event);

		Layer* PushLayer(uniquePtr<Layer> layer);

	protected:
		Application(std::string&& windowName = "Application");
		
	private:
		static Application* s_Application;
		uniquePtr<Window> m_Window;
		EventHandler m_EventHandler;
        LayerStack m_layerStack;
        uniquePtr<Device> m_SoundDevice;
	};

} // namespace Aquarius
