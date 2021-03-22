#include "LevelEditorLayer.h"

LevelEditorLayer::LevelEditorLayer()
	: Layer("LevelEditor", true) 
{}

void LevelEditorLayer::onCreation()
{
	// Initialization
	AQ_INFO("LEVEL CREATED");
	Aquarius::Application* app = Aquarius::Application::get();
	Aquarius::Window* window = app->getWindow();

	int height = window->getHeight();
	int width = window->getWidth();

	m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);

	Aquarius::Renderer::Init();
}

void LevelEditorLayer::onUpdate(Aquarius::timeDelta_t time)
{
	Aquarius::Renderer::BeginScene(m_Camera.get());
	Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
	Aquarius::Renderer::Clear();
}

void LevelEditorLayer::onDestruction()
{
	// Cleanup
	AQ_INFO("Level editor layer destroyed");
}
