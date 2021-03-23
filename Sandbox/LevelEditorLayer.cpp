#include "LevelEditorLayer.h"

LevelEditorLayer::LevelEditorLayer()
	: Layer("LevelEditor", true) 
{}

void LevelEditorLayer::onCreation()
{
	// Camera setup
	Aquarius::Application* app = Aquarius::Application::get();
	Aquarius::Window* window = app->getWindow();

	int height = window->getHeight();
	int width = window->getWidth();

	m_camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.005, height, width);

	// Create spritesheet and level
	Aquarius::TextureConfiguration spriteMapTexConfig = {
	Aquarius::TextureWrapOption::Repeat,
	Aquarius::TextureWrapOption::Repeat,
	Aquarius::TextureFilteringOption::Nearest,
	Aquarius::TextureFilteringOption::Nearest
	};

	m_spriteSheetTexture = std::make_unique<Aquarius::Texture>("Sandbox/Assets/tilemap_packed.png", spriteMapTexConfig, true);
	m_spritesheet = std::make_unique<Aquarius::SpriteSheet>(m_spriteSheetTexture.get(), 16, 16);
	m_level = std::make_unique<Level>(m_spritesheet.get(), 800, 600, 64, 64, "Level 1");

	int levelHeight = m_level->getHeight();
	int levelWidth = m_level->getWidth();

	for (int i = 0; i < levelHeight; i++)
	{
		for (int j = 0; j < levelWidth; j++)
		{
			m_level->setTile(i, j, 0, 0);
		}
	}

	Aquarius::Renderer::Init();
}

void LevelEditorLayer::onUpdate(Aquarius::timeDelta_t time)
{
	Aquarius::Renderer::BeginScene(m_camera.get());
	Aquarius::Renderer::ClearColor({0, 0, 0});
	Aquarius::Renderer::Clear();

	//m_camera->onUpdate(time);
	m_level->draw();

	AQ_INFO("FPS: %v", 1000.0 / time);
}

void LevelEditorLayer::onDestruction()
{
	// Cleanup
	AQ_INFO("Level editor layer destroyed");
}
