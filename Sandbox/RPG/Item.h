#pragma once 

#include "Aquarius.h"

#include <string>


// Represents generic inventory items
class Item
{
public:
	Item(const glm::vec2& pos,
		 const glm::vec2& size, 
		 Aquarius::Texture* sprite, 
		 Aquarius::QuadTexCoords* texCoords,
		 const std::string& name) 
			: m_position(pos), 
			  m_size(size), 
			  m_spriteTexture(sprite),
			  m_spriteTexCoords(texCoords),
			  m_name(name)
	{}

	~Item() = default;
	
	glm::vec2 m_position;
	glm::vec2 m_size;
	Aquarius::Texture* m_spriteTexture;
	Aquarius::QuadTexCoords* m_spriteTexCoords;
	std::string m_name;
	
	void draw() const
	{
		Aquarius::Renderer::DrawQuad(
			m_position,
			m_size,
			m_spriteTexture,
			m_spriteTexCoords
		);
	}
};
