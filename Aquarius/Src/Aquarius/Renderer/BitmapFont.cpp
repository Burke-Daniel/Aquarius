#include "BitmapFont.h"

#include "Aquarius/Renderer/Renderer.h"

#include <unordered_map>


namespace Aquarius {

	static const std::unordered_map<char, std::pair<uint32_t, uint32_t>> characterLocations =
	{
		{'A', {8, 5}},
		{'B', {9, 5}},
		{'C', {10, 5}},
		{'D', {11, 5}},
		{'E', {0, 4}},
		{'F', {1, 4}},
		{'G', {2, 4}},
		{'H', {3, 4}},
		{'I', {4, 4}},
		{'J', {5, 4}},
		{'K', {6, 4}},
		{'L', {7, 4}},
		{'M', {8, 4}},
		{'N', {9, 4}},
		{'O', {10, 4}},
		{'P', {11, 4}},
		{'Q', {0, 3}},
		{'R', {1, 3}},
		{'S', {2, 3}},
		{'T', {3, 3}},
		{'U', {4, 3}},
		{'V', {5, 3}},
		{'W', {6, 3}},
		{'X', {7, 3}},
		{'Y', {8, 3}},
		{'Z', {9, 3}},
		{'0', {3, 6}},
		{'1', {4, 6}},
		{'2', {5, 6}},
		{'3', {6, 6}},
		{'4', {7, 6}},
		{'5', {8, 6}},
		{'6', {9, 6}},
		{'7', {10, 6}},
		{'8', {11, 6}},
		{'9', {12, 5}},
		{'-', {0, 6}},
		{' ', {11, 0}}
	};

	Bitmap::Bitmap(Texture* texture, uint32_t fontWidth, uint32_t fontHeight)
		: SpriteSheet(texture, fontWidth, fontHeight)
	{}

	void Bitmap::CreateBitmap(Texture* texture, uint32_t fontWidth, uint32_t fontHeight)
	{
		CreateSpriteSheet(texture, fontWidth, fontHeight);
	}

	void Bitmap::RenderCharacter(char c, const glm::vec2& pos, float sizeMultiplier, const glm::vec4& color)
	{
		auto texCoords = getSpriteCoords(characterLocations.at(c).first, characterLocations.at(c).second);
		Renderer::DrawQuad(
			pos,
			glm::vec2(m_SpriteWidth * sizeMultiplier, m_SpriteHeight * sizeMultiplier),
			m_Texture,
			&texCoords,
			0.0,
			color
		);
	}

	void Bitmap::RenderText(const std::string& text, const glm::vec2& pos, float sizeMultiplier, const glm::vec4& color)
	{
		auto xOffset = pos.x;
		for (const auto c : text)
		{
			RenderCharacter(c, glm::vec2(xOffset, pos.y), sizeMultiplier, color);
			xOffset += m_SpriteWidth * sizeMultiplier;
		}
	}

} // namespace Aquarius
