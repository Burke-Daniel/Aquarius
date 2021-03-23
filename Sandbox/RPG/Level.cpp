#include "Level.h"


Level::Level(Aquarius::SpriteSheet* spritesheet,
			 uint32_t mapWidth,
			 uint32_t mapHeight,
			 uint32_t tileWidth,
			 uint32_t tileHeight,
			 const std::string& name)
{
	// Height and width of the screen in number of textures 
	m_name = name;
	m_spritesheet = spritesheet;
	m_tileHeight = tileHeight;
	m_tileWidth = tileWidth;
	m_height = mapHeight;
	m_width = mapWidth;
	m_map = std::vector<std::vector<Tile>>(m_height, std::vector<Tile>(m_width));

	auto texCoords = Aquarius::QuadTexCoords();

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			float x = j * m_tileWidth;
			float y = i * m_tileHeight;
			m_map[i][j] = { 0, 0, x, y, texCoords, true };
		}
	}
}

void Level::setTile(int mapI, int mapJ, int spriteI, int spriteJ)
{
	m_map[mapI][mapJ].i = spriteI;
	m_map[mapI][mapJ].j = spriteJ;
	Aquarius::QuadTexCoords texCoords = m_spritesheet->getSpriteCoords(spriteI, spriteJ);
	m_map[mapI][mapJ].texCoords = texCoords;
	m_map[mapI][mapJ].clear = false;
}

void Level::clearTile(int mapI, int mapJ)
{
	m_map[mapI][mapJ].i = 0;
	m_map[mapI][mapJ].j = 0;
	auto texCoords = Aquarius::QuadTexCoords();
	m_map[mapI][mapJ].texCoords = texCoords;
	m_map[mapI][mapJ].clear = true;
}

void Level::draw()
{
	// Draw each of the map tiles
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			Aquarius::Renderer::DrawQuad(
				{m_map[i][j].x, m_map[i][j].y},
				{m_tileWidth, m_tileHeight},
				m_spritesheet->getTexture(),
				&m_map[i][j].texCoords,
				0.0f
			);
		}
	}
}
