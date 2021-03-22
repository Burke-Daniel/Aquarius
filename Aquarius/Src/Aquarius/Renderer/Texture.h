#pragma once

#include <array>
#include <cstdint>
#include <glad/glad.h>
#include <glm/glm.hpp>
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
		Texture(TextureConfiguration configuration = {}) : m_Configuration(configuration) {}
		~Texture();

		bool generateTexture(const std::string& texture, bool hasAlpha = false);
		bool generateSolidTexture(std::array<uint8_t, 4> color);

		void bind(uint32_t textureSlot) const;
		void unbind() const;

		int getWidth() const { return m_Width; }
		int getHeight() const { return m_Height; }
		int getNumColorChannels() const { return m_NumColorChannels; }

		void setConfiguration(const TextureConfiguration& configuration) { m_Configuration = configuration; }

	private:
		uint32_t m_ID = 0;
		int m_Width = 0;
		int m_Height = 0;
		int m_NumColorChannels = 0;
		TextureConfiguration m_Configuration;
	};

} // namespace Aquarius
