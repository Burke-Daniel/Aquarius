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
		auto bottomLeftX = i * ((float)m_SpriteWidth / (float)m_TotalWidth);
		auto bottomLeftY = (j + 1) * ((float)m_SpriteHeight / (float)m_TotalHeight);

		auto bottomRightX = (i + 1) * ((float)m_SpriteWidth / (float)m_TotalWidth);
		auto bottomRightY = (j + 1) * ((float)m_SpriteHeight / (float)m_TotalHeight);

		auto topRightX = (i + 1) * ((float)m_SpriteWidth / (float)m_TotalWidth);
		auto topRightY = j * ((float)m_SpriteHeight / (float)m_TotalHeight);

		auto topLeftX = i * ((float)m_SpriteWidth / (float)m_TotalWidth);
		auto topLeftY = j * ((float)m_SpriteHeight / (float)m_TotalHeight);

		return QuadTexCoords {
			{ bottomLeftX, bottomLeftY },
			{ bottomRightX, bottomRightY },
			{ topRightX, topRightY },
			{ topLeftX, topLeftY }
		};
	}

} // namespace Aquarius