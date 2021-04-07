#pragma once
#include "Aquarius.h"

static int id = 0;
class Entity
{
public:
	Entity(const glm::vec2& pos,
		const glm::vec2& scale,
		const glm::vec4& color,
		float rot,
		bool animate = false)
		: m_position(pos),
		m_scale(scale),
		m_color(color),
		m_rotation(rot),
		m_isAnimated(animate),
		m_animationSpeed(0)
	{
		m_id = id++;
	}

	~Entity() = default;

	void onUpdate(Aquarius::timeDelta_t time)
	{
		if (m_isAnimated)
		{
			m_rotation = m_rotation > 360 ? 0 : m_rotation + time * m_animationSpeed;
		}
	}

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
	bool m_isAnimated;
	float m_animationSpeed;
};
