#include "LevelEditorLayer.h"
#include "Item.h"

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
	
	m_coordMap.insert({ "traffic_light", m_spritesheet->getSpriteCoords(6, 2) });
	m_coordMap.insert({ "cone", m_spritesheet->getSpriteCoords(10, 6) });
	m_coordMap.insert({ "bench", m_spritesheet->getSpriteCoords(3, 3) });

	m_level = std::make_unique<Level>(m_spritesheet.get(), 16, 16, 64, 64, "Level 1");

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

	m_playerTexture = std::make_unique<Aquarius::Texture>("Sandbox/Assets/PlayerSpriteSheet.png", spriteMapTexConfig, true);
	m_playerSpritesheet = std::make_unique<Aquarius::SpriteSheet>(m_playerTexture.get(), 16, 16);

	m_player = std::make_unique<Player>(
		m_spritesheet.get(),
		m_MoveSpeed,
		glm::vec2{64, 64},
		glm::vec2{64, 64},
		0.0,
		m_level.get()
	);

	for (int i = 0; i < 1000; i++)
	{
		Item* cone = new Item({ 0, 0 },
			{ 64, 64 },
			m_spriteSheetTexture.get(),
			&m_coordMap.at("cone"),
			"cone");

		Item* traffic_light = new Item({ 0, 0 },
			{ 64, 64 },
			m_spriteSheetTexture.get(),
			&m_coordMap.at("traffic_light"),
			"traffic_light");

		Item* bench = new Item({ 0, 0 },
			{ 64, 64 },
			m_spriteSheetTexture.get(),
			&m_coordMap.at("bench"),
			"bench");

		m_player->addItem(cone);
		m_player->addItem(traffic_light);
		m_player->addItem(bench);
	}

	m_activeItemToolbar = std::make_unique<Toolbar>(
		glm::vec2{84, 84},
		m_spriteSheetTexture.get(),
		m_player->getActiveItem()->m_spriteTexCoords
	);

	m_activeItemToolbar->setAlignment(ToolbarAlignment::TopLeft);
	
	// TODO
	glfwSetInputMode(window->get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	Aquarius::Renderer::Init();
}

void LevelEditorLayer::onUpdate(Aquarius::timeDelta_t time)
{
	Aquarius::Renderer::BeginScene(m_camera.get());
	Aquarius::Renderer::ClearColor({0, 0, 0});
	Aquarius::Renderer::Clear();

	// Toggle demo window
	if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_m))
	{
		m_MenuOpen = true;
	}

	m_player->onUpdate(time);
	
	Item* activeItem = m_player->getActiveItem();

	if (activeItem != nullptr)
	{
		m_activeItemToolbar->setActiveItemIcon(
			m_spriteSheetTexture.get(),
			m_player->getActiveItem()->m_spriteTexCoords
		);
	}
	else
	{
		m_activeItemToolbar->setActiveItemIcon(
			m_spriteSheetTexture.get(),
			nullptr
		);
	}

	m_level->draw();
	m_player->draw();
	m_activeItemToolbar->draw();

	AQ_TRACE("FPS: %v", 1000.0 / time);
}

void LevelEditorLayer::onUpdateGUI(Aquarius::timeDelta_t time)
{

	if (m_MenuOpen)
	{
		ImGui::Begin("RPG Demo", &m_MenuOpen);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Top Down RPG Demo!");
		if (ImGui::CollapsingHeader("Controls"))
		{
			ImGui::Text("1. To move, use WASD");
			ImGui::Text("2. To cycle through available items, scroll up/down");
			ImGui::Text("3. To place an item, press left mouse button.");
		}

		if (ImGui::CollapsingHeader("Configuration"))
		{
			ImGui::Text("To aid the demo, a couple of options are configurable here!");
			ImGui::DragFloat("Move speed", &m_MoveSpeed, 0.01, 0.001, 2);
			ImGui::DragFloat4("UI Color", m_toolbarColor, 0.01, 0, 1);

			m_activeItemToolbar->setColor({m_toolbarColor[0], m_toolbarColor[1], m_toolbarColor[2], m_toolbarColor[3]});
			m_player->setMovespeed(m_MoveSpeed);
		}

		if (ImGui::CollapsingHeader("Profiling"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
				1000.0f / ImGui::GetIO().Framerate,
				ImGui::GetIO().Framerate);
		}

		ImGui::End();
	}
}

void LevelEditorLayer::onDestruction()
{
	// Cleanup
}
