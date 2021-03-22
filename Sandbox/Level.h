#include "Aquarius.h"

#include <array>
#include <string> 

class Level
{
public:
	Level();
	~Level() = default;

	void Draw();
	void Serialize();
	void Load();

	struct Tile
	{
		// Tilemap Coordinates
		int i;
		int j;

		// World Coordinates
		float x; 
		float y;
	};

private:
	std::string m_name;
	int m_height;
	int m_width;
	std::vector<std::vector<Tile>> m_map;
};

