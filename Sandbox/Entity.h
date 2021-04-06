#pragma once
#include "Aquarius.h"

static int id = 0;
class Entity
{
public:
	Entity(const glm::vec2& pos,
		   const glm::vec2& scale,
		   const glm::vec4& color,
		   float rot)	
		:	m_position(pos),
			m_scale(scale),
			m_color(color),
			m_rotation(rot) 
	{
		m_id = id++;
	}

	~Entity() = default;

	void draw() const 
	{
		Aquarius::Renderer::DrawQuad(
			m_position,
			m_scale,
			m_rotation,
			m_color
		);
	}

	int m_id;
	glm::vec2 m_position;
	glm::vec2 m_scale;
	glm::vec4 m_color;
	float m_rotation;
};