#pragma once

#include "stb_image.h"

#include "Aquarius.h"

#include <cstdint>
#include <string>


namespace Aquarius {
	
	enum class TextureWrapOption : int
	{
		Repeat = GL_REPEAT,
		MirroredRepeat = GL_MIRRORED_REPEAT,
		ClampToEdge = GL_CLAMP_TO_EDGE,
		ClampToBorder = GL_CLAMP_TO_BORDER
	};

	enum class TextureFilteringOption : int
	{
		Linear = GL_LINEAR,
		Nearest = GL_NEAREST
	};

	struct TextureConfiguration
	{
		TextureWrapOption textureWrapS = TextureWrapOption::Repeat;
		TextureWrapOption textureWrapT = TextureWrapOption::Repeat;
		TextureFilteringOption minTextureFiltering = TextureFilteringOption::Linear;
		TextureFilteringOption magTextureFiltering = TextureFilteringOption::Linear;
	};

	class Texture
	{
	public:
		Texture(const std::string& texture, TextureConfiguration configuration = {}, bool hasAlpha = false);

		bool generateTexture(const std::string& texture, bool hasAlpha = false);

		void bind() const;
		void unbind() const;

		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		int getNumColorChannels() const { return m_NumColorChannels; }

		void setConfiguration(const TextureConfiguration& configuration) { m_Configuration = configuration; }

	private:
		static uint8_t s_NextTextureUnitNum;
		int m_TextureUnitNum;
		uint32_t m_ID = 0;
		int m_Width = 0;
		int m_Height = 0;
		int m_NumColorChannels = 0;
		TextureConfiguration m_Configuration;
	};

}
