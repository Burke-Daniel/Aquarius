#pragma once

#include "Aquarius/Renderer/SpriteSheet.h"

#include "glm/glm.hpp"

#include <string>


namespace Aquarius {

	class Texture;

	class Bitmap : public SpriteSheet
	{
	public:
		Bitmap(Texture* texture, uint32_t fontWidth, uint32_t fontHeight);

		void CreateBitmap(Texture* texture, uint32_t fontWidth, uint32_t fontHeight);

		void RenderCharacter(char c, const glm::vec2& pos, float sizeMultiplier = 1.0, const glm::vec4& color = { 1.0, 1.0, 1.0, 1.0 });
		void RenderText(const std::string& text, const glm::vec2& pos, float sizeMultiplier = 1.0, const glm::vec4& color = { 1.0, 1.0, 1.0, 1.0 });
	};

} // namespace Aquarius
