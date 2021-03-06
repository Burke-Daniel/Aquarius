#include "Texture.h"


namespace Aquarius {

	uint8_t Texture::s_NextTextureUnitNum = 0;

	Texture::Texture(const std::string& texture, TextureConfiguration configuration, bool hasAlpha)
		: m_Configuration(configuration)
	{
		generateTexture(texture, hasAlpha);
	}

	bool Texture::generateTexture(const std::string& texture, bool hasAlpha)
	{
		bool success = false;

		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		m_TextureUnitNum = GL_TEXTURE0 + s_NextTextureUnitNum++;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(m_Configuration.textureWrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(m_Configuration.textureWrapT));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(m_Configuration.minTextureFiltering));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(m_Configuration.magTextureFiltering));
		unsigned char* data = stbi_load(texture.c_str(), &m_Width, &m_Height, &m_NumColorChannels, 0);
		
		if (data != nullptr)
		{
			int format = hasAlpha ? GL_RGBA : GL_RGB;

			glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			success = true;
		}
		else
		{
			AQ_CORE_WARNING("Failed to load texture from: %v", texture);
		}

		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);

		return success;
	}

	void Texture::bind() const
	{
		glActiveTexture(m_TextureUnitNum);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}
