#include "SpriteSheet.h"

#include "QuadTexCoords.h"


namespace Aquarius {

	SpriteSheet::SpriteSheet(Texture* texture, uint32_t spriteWidth, uint32_t spriteHeight)
	{
		CreateSpriteSheet(texture, spriteWidth, spriteHeight);
	}

	void SpriteSheet::CreateSpriteSheet(Texture* texture, uint32_t spriteWidth, uint32_t spriteHeight)
	{
		m_Texture = texture;
		m_TotalWidth = texture->getWidth();
		m_TotalHeight = texture->getHeight();
		m_SpriteWidth = spriteWidth;
		m_SpriteHeight = spriteHeight;
	}

	QuadTexCoords SpriteSheet::getSpriteCoords(uint32_t i, uint32_t j) const
	{
		// Bottom Left Zero Indexed
		glm::vec2 bottomLeft = { i * ((float)m_SpriteWidth / (float)m_TotalWidth), j * ((float)m_SpriteHeight / (float)m_TotalHeight) };
		glm::vec2 bottomRight = { (i + 1) * ((float)m_SpriteWidth / (float)m_TotalWidth), j * ((float)m_SpriteHeight / (float)m_TotalHeight) };
		glm::vec2 topRight = { (i + 1) * ((float)m_SpriteWidth / (float)m_TotalWidth), (j + 1) * ((float)m_SpriteHeight / (float)m_TotalHeight) };
		glm::vec2 topLeft = { i * ((float)m_SpriteWidth / (float)m_TotalWidth), (j + 1) * ((float)m_SpriteHeight / (float)m_TotalHeight) };

		std::array<glm::vec2, 4> texCoords = { bottomLeft, bottomRight, topRight, topLeft };

		return texCoords;
	}

} // namespace Aquarius
