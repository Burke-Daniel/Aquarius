#include "LevelEditorLayer.h"


static std::vector<std::vector<glm::ivec2>> MapTiles =
{
	{ {0,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {0,2}, {0,0}, {0,0}, {0,0} },
	{ {0,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {0,1}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {0,0}, {0,0}, {0,0}, {0,0} },
	{ {0,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {0,2}, {0,0}, {0,0}, {0,0} },
	{ {0,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {0,1}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {0,0}, {0,0}, {0,0}, {0,0} },
	{ {0,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {1,2}, {0,2}, {0,0}, {0,0}, {0,0} },
	{ {0,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {1,1}, {0,1}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {1,0}, {0,0}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} },
	{ {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0} }
};

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
	m_level = std::make_unique<Level>(m_spritesheet.get(), 16, 16, 64, 64, "Level 1");

	m_playerTexture = std::make_unique<Aquarius::Texture>("Sandbox/Assets/PlayerSpriteSheet.png", spriteMapTexConfig, true);
	m_playerSpritesheet = std::make_unique<Aquarius::SpriteSheet>(m_playerTexture.get(), 16, 16);

	m_player = std::make_unique<Player>(
		m_spritesheet.get(),
		0.2,
		glm::vec2{64, 64},
		glm::vec2{64, 64},
		0.0
	);

	m_coordMap.insert({ "traffic_light", m_spritesheet->getSpriteCoords(6, 2) });
	m_coordMap.insert({"cone", m_spritesheet->getSpriteCoords(10, 6)});
	m_coordMap.insert({ "bench", m_spritesheet->getSpriteCoords(3, 3) });

	int levelHeight = m_level->getHeight();
	int levelWidth = m_level->getWidth();

	// Populate tiles
	for (int i = 0; i < levelHeight; i++)
	{
		for (int j = 0; j < levelWidth; j++)
		{
			m_level->setTile(i, j, MapTiles[i][j][0], MapTiles[i][j][1]);
		}
	}

	Aquarius::Renderer::Init();
}

void LevelEditorLayer::onUpdate(Aquarius::timeDelta_t time)
{
	Aquarius::Renderer::BeginScene(m_camera.get());
	Aquarius::Renderer::ClearColor({0, 0, 0});
	Aquarius::Renderer::Clear();

	m_player->onUpdate(time);
	m_level->draw();

	Aquarius::Renderer::DrawQuad(
		m_level->getTileWorldCoords(2, 7),
		{ 64, 64 },
		m_spriteSheetTexture.get(),
		&m_coordMap.at("bench")
	);

	Aquarius::Renderer::DrawQuad(
		m_level->getTileWorldCoords(5, 7),
		{ 64, 64 },
		m_spriteSheetTexture.get(),
		&m_coordMap.at("bench")
	);

	Aquarius::Renderer::DrawQuad(
		m_level->getTileWorldCoords(3, 3),
		{ 64, 64 },
		m_spriteSheetTexture.get(),
		&m_coordMap.at("cone")
	);

	Aquarius::Renderer::DrawQuad(
		m_level->getTileWorldCoords(4, 3),
		{ 64, 64 },
		m_spriteSheetTexture.get(),
		&m_coordMap.at("cone")
	);

	Aquarius::Renderer::DrawQuad(
		m_level->getTileWorldCoords(5, 3),
		{ 64, 64 },
		m_spriteSheetTexture.get(),
		&m_coordMap.at("cone")
	);

	Aquarius::Renderer::DrawQuad(
		m_level->getTileWorldCoords(0, 0),
		{ 64, 64 },
		m_spriteSheetTexture.get(),
		&m_coordMap.at("traffic_light")
	);

	Aquarius::Renderer::DrawQuad(
		m_level->getTileWorldCoords(3, 0),
		{ 64, 64 },
		m_spriteSheetTexture.get(),
		&m_coordMap.at("traffic_light")
	);

	Aquarius::Renderer::DrawQuad(
		m_level->getTileWorldCoords(6, 0),
		{ 64, 64 },
		m_spriteSheetTexture.get(),
		&m_coordMap.at("traffic_light")
	);


	m_player->draw();
	AQ_TRACE("FPS: %v", 1000.0 / time);
}

void LevelEditorLayer::onDestruction()
{
	// Cleanup
}
