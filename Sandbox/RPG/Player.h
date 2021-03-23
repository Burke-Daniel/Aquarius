#pragma once 

#include "Aquarius.h"
#include <chrono>


class Player
{
public:
	enum class PlayerState
	{
		IDLING,
		WALKING_RIGHT,
		WALKING_LEFT,
		WALKING_UP,
		WALKING_DOWN,
	};

	Player(Aquarius::SpriteSheet* spritesheet, 
		   float moveSpeed, 
		   const glm::vec2& scale,
		   const glm::vec2& position,
		   float rotation)
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;
		m_spritesheet = spritesheet;
		m_moveSpeed = moveSpeed;
		m_spriteTexture = m_spritesheet->getTexture();
		m_count = 0;
		m_walkInterval = 100;
		m_offset = 0;

		m_walkLeftFrames = {    
			m_spritesheet->getSpriteCoords(0 + 23,2 + 6),
			m_spritesheet->getSpriteCoords(0 + 23,1 + 6),
			m_spritesheet->getSpriteCoords(0 + 23,2 + 6),
			m_spritesheet->getSpriteCoords(0 + 23,0 + 6),
		};											
													
		m_walkRightFrames =  {     					
			m_spritesheet->getSpriteCoords(3 + 23,2 + 6),
			m_spritesheet->getSpriteCoords(3 + 23,1 + 6),
			m_spritesheet->getSpriteCoords(3 + 23,2 + 6),
			m_spritesheet->getSpriteCoords(3 + 23,0 + 6)
		};											
													
		m_walkUpFrames = {							
			m_spritesheet->getSpriteCoords(2 + 23,2 + 6),
			m_spritesheet->getSpriteCoords(2 + 23,1 + 6),
			m_spritesheet->getSpriteCoords(2 + 23,2 + 6),
			m_spritesheet->getSpriteCoords(2 + 23,0 + 6)
		};											
													
		m_walkDownFrames = {						
			m_spritesheet->getSpriteCoords(1 + 23,2 + 6),
			m_spritesheet->getSpriteCoords(1 + 23,1 + 6),
			m_spritesheet->getSpriteCoords(1 + 23,2 + 6),
			m_spritesheet->getSpriteCoords(1 + 23,0 + 6)
		};

		m_idlingFrames = {
			m_spritesheet->getSpriteCoords(1 + 23,2 + 6)
		};

		m_playerState = PlayerState::IDLING;
		m_playerPreviousState = PlayerState::IDLING;
	}

	~Player() = default;

	glm::vec2 getPosition() const { return m_position; }
	glm::vec2 getScale() const { return m_scale; }
	float getRotation() const { return m_rotation; }
	

	void onUpdate(Aquarius::timeDelta_t ts) // ms 
	{
		float dx = m_moveSpeed * ts;
		m_count += ts;

		if (m_count >= m_walkInterval)
		{
			m_count = 0;

			if (m_offset >= m_activeFrames->size())
			{
				m_offset = 0;
			}
			m_activeSprite = m_activeFrames->at(m_offset);

			m_offset++;
		}

		m_playerState = PlayerState::IDLING;

		// Up
		if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_w))
		{
			m_playerState = PlayerState::WALKING_UP;
			m_position.y -= dx;;
		}

		// Down
		if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_s))
		{
			m_playerState = PlayerState::WALKING_DOWN;
			m_position.y += dx;
		}

		// Left
		if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_a))
		{
			m_playerState = PlayerState::WALKING_LEFT;
			m_position.x -= dx;
		}

		// Right
		if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_d))
		{
			m_playerState = PlayerState::WALKING_RIGHT;
			m_position.x += dx;
		}

		if (m_position.x + m_scale.x > m_app->getWindow()->getWidth())
		{
			m_position.x = m_app->getWindow()->getWidth() - m_scale.x;
		}

		if (m_position.x < 0)
		{
			m_position.x = 0;
		}

		if (m_position.y + m_scale.y > m_app->getWindow()->getHeight())
		{
			m_position.y = m_app->getWindow()->getHeight() - m_scale.y;
		}

		if (m_position.y < 0)
		{
			m_position.y = 0;
		}

		updateState();
	};

	void updateState()
	{
		switch (m_playerState)
		{
		case PlayerState::WALKING_LEFT:
			m_activeFrames = &m_walkLeftFrames;
			break;
		case PlayerState::WALKING_RIGHT:
			m_activeFrames = &m_walkRightFrames;
			break;
		case PlayerState::WALKING_DOWN:
			m_activeFrames = &m_walkDownFrames;
			break;
		case PlayerState::WALKING_UP:
			m_activeFrames = &m_walkUpFrames;
			break;
		case PlayerState::IDLING:
			m_activeFrames = &m_idlingFrames;
			break;
		}

		// If state changed immediately update sprite
		if (m_playerState != m_playerPreviousState)
		{
			m_offset = 0;
			m_count = m_walkInterval;
		}

		m_playerPreviousState = m_playerState;
	}

	void draw()
	{
		Aquarius::Renderer::DrawQuad(
			m_position,
			m_scale,
			m_spriteTexture,
			&m_activeSprite
		);
	}

private:
	PlayerState m_playerState;
	PlayerState m_playerPreviousState;

	glm::vec2 m_position;
	float m_rotation;
	glm::vec2 m_scale;
	float m_moveSpeed;

	Aquarius::SpriteSheet* m_spritesheet;
	Aquarius::Texture* m_spriteTexture;
	Aquarius::QuadTexCoords m_activeSprite;

	std::vector<Aquarius::QuadTexCoords> m_walkLeftFrames;
	std::vector<Aquarius::QuadTexCoords> m_walkRightFrames;
	std::vector<Aquarius::QuadTexCoords> m_walkUpFrames;
	std::vector<Aquarius::QuadTexCoords> m_walkDownFrames;
	std::vector<Aquarius::QuadTexCoords> m_idlingFrames;
	std::vector<Aquarius::QuadTexCoords>* m_activeFrames;
	int m_offset;

	Aquarius::timeDelta_t m_count;
	Aquarius::timeDelta_t m_walkInterval;
	Aquarius::Application* m_app = Aquarius::Application::get();
};
