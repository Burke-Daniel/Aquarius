#include "ManagerLayer.h"


ManagerLayer::ManagerLayer(std::vector<Aquarius::Layer*> layers)
	: Layer("Manager", true), m_ManagedLayers(layers)
{}

void ManagerLayer::onCreation()
{
	Aquarius::Application& app = *Aquarius::Application::get();

	app.getEventHandler().subscribe(Aquarius::eventType::KeyPressedEvent,
		[&](const Aquarius::Event& event)
		{
			onEvent(event);
		});

	for (const auto layer : m_ManagedLayers)
	{
		layer->deactivate();
	}

	if (!m_ManagedLayers.empty())
	{
		m_ManagedLayers.front()->activate();
		m_ActiveLayerIndex = 0;
	}
}

void ManagerLayer::onEvent(const Aquarius::Event& event)
{
	auto keyPressEvent = static_cast<const Aquarius::KeyPressedEvent&>(event);

	switch (keyPressEvent.getCode())
	{
		case (Aquarius::Input::KeyCode::Key_page_up):
        case (Aquarius::Input::KeyCode::Key_f):
		{
			if (m_ActiveLayerIndex < m_ManagedLayers.size() - 1)
			{
				m_ManagedLayers[m_ActiveLayerIndex]->deactivate();
				m_ManagedLayers[++m_ActiveLayerIndex]->activate();
			}
			break;
		}

		case (Aquarius::Input::KeyCode::Key_page_down):
        case (Aquarius::Input::KeyCode::Key_b):
		{
			if (m_ActiveLayerIndex > 0)
			{
				m_ManagedLayers[m_ActiveLayerIndex]->deactivate();
				m_ManagedLayers[--m_ActiveLayerIndex]->activate();
			}
			break;
		}
	}
}
