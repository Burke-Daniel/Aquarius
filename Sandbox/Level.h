#include "Aquarius.h"

#include <array>
#include <string> 

class Level
{
public:
	struct Tile;
	Level(Aquarius::SpriteSheet* spritesheet, 
		  uint32_t screenWidth, 
		  uint32_t screenHeight, 
		  uint32_t tileWidth,
		  uint32_t tileHeight,
		  const std::string& name
		);

	~Level() = default;

	void setTile(int mapI, int mapJ, int spriteI, int spriteJ);

	void clearTile(int mapI, int mapJ);

	// Draw each of the textured quads in the world
	void draw();

	// Save the map to a file
	void serialize();

	int getHeight() const { return m_height; };
	int getWidth() const { return m_width; };

	struct Tile
	{
		// Tilemap Coordinates
		int i;
		int j;

		// World Coordinates
		float x; 
		float y;

		// Texture coords
		Aquarius::QuadTexCoords texCoords;

		bool clear;
	};

private:
	std::string m_name;
	Aquarius::SpriteSheet* m_spritesheet;
	int m_height;
	int m_width;
	int m_tileHeight;
	int m_tileWidth;

	// TODO Could be an array
	std::vector<std::vector<Tile>> m_map;
};

