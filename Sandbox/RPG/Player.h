#pragma once 

#include "Aquarius.h"
#include "Level.h"

#include <chrono>
#include <unordered_map>


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
		   float rotation,
		   Level* level)
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;
		m_spritesheet = spritesheet;
		m_moveSpeed = moveSpeed;
		m_spriteTexture = m_spritesheet->getTexture();
		m_level = level;
		m_count = 0;
		m_walkInterval = 100;
		m_offset = 0;
		m_itemTypes = { "" };
		m_activeItemIt = m_itemTypes.begin();

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


		// Register mouse wheel event
		Aquarius::Application::get()->getEventHandler().subscribe(Aquarius::eventType::MouseScrolledEvent,
			[&](const Aquarius::Event& event)
			{
				onMouseWheel(event);
			});

		Aquarius::Application::get()->getEventHandler().subscribe(Aquarius::eventType::MouseButtonReleasedEvent,
			[&](const Aquarius::Event& event)
			{
				onMouseReleased(event);
			});
	}

	~Player()
	{
		for (const std::string& type : m_itemTypes)
		{
			for (const Item* item : m_inventory[type])
			{
				delete item;
				item = nullptr;
			}
		}
	}

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
			if (!(m_position.y <= 0))
			{
				m_position.y -= dx;
			}
		}

		// Down
		if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_s))
		{
			m_playerState = PlayerState::WALKING_DOWN;
			if (!(m_position.y + m_scale.y >= m_app->getWindow()->getHeight()))
			{
				m_position.y += dx;
			}
		}

		// Left
		if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_a))
		{
			m_playerState = PlayerState::WALKING_LEFT;
			if (!(m_position.x <= 0))
			{
				m_position.x -= dx;
			}
		}

		// Right
		if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_d))
		{
			m_playerState = PlayerState::WALKING_RIGHT;

			if (! (m_position.x + m_scale.x >= m_app->getWindow()->getWidth() ) )
			{
				m_position.x += dx;
			}
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

	void addItem(Item* item)
	{
		// If the bucket for this item type exists
		if (m_inventory.find(item->m_name) == m_inventory.end()) 
		{
			m_inventory[item->m_name] = std::vector<Item*>{ item };
			m_itemTypes.push_back(item->m_name);
			m_activeItemIt = m_itemTypes.end() - 1;
		}
		else 
		{
			m_inventory[item->m_name].push_back(item);
		}
	}

	int getItemCount(const std::string& item)
	{
		if (m_inventory.find(item) == m_inventory.end()) 
		{
			return 0;
		}	
		else 
		{
			return m_inventory[item].size();
		}
	}

	Item* popItem(const std::string& item)
	{
		if (m_inventory.find(item) == m_inventory.end())
		{
			return nullptr;
		}
		else 
		{
			Item* lastItem = m_inventory[item].back();
			m_inventory[item].pop_back();

			// All items are gone 
			if (m_inventory[item].size() == 0)
			{
				m_inventory.erase(item);

				if (item == *m_activeItemIt)
				{
					m_activeItemIt = m_itemTypes.erase(m_activeItemIt);
					if (m_activeItemIt == m_itemTypes.end())
					{
						m_activeItemIt = m_itemTypes.begin();
					}
				}
			}

			return lastItem;
		}
	}

	// Next item to be popped of that type
	Item* peekItem(const std::string& item)
	{
		if (m_inventory.find(item) == m_inventory.end())
		{
			return nullptr;
		}
		else
		{
			Item* lastItem = m_inventory[item].back();
			return lastItem;
		}
	}

	void placeActiveItem()
	{
		Item* item = popItem(*m_activeItemIt);

		if (item == nullptr)
		{
			return;
		}

		item->m_position = m_position;
		m_level->addItem(item);
	}

	Item* getActiveItem()
	{
		return peekItem(*m_activeItemIt);
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

	void onMouseWheel(const Aquarius::Event& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		bool imguiConsumingMouse = io.WantCaptureMouse;

		if (imguiConsumingMouse)
		{
			return;
		}

		auto e = static_cast<const Aquarius::MouseScrolledEvent&>(event);
		int yOffset = e.getYOffset();

		if (m_itemTypes.size() != 0)
		{
			// Scrolled up
			if (yOffset == 1)
			{
				m_activeItemIt++;
				if (m_activeItemIt == m_itemTypes.end())
				{
					m_activeItemIt = m_itemTypes.begin();
				}
			}
			else
			{
				if (m_activeItemIt == m_itemTypes.begin())
				{
					m_activeItemIt = m_itemTypes.end() - 1;
				}
				else
				{
					m_activeItemIt--;
				}
			}
		}
	}

	void onMouseReleased(const Aquarius::Event& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		bool imguiConsumingMouse = io.WantCaptureMouse;

		auto e = static_cast<const Aquarius::MouseButtonReleasedEvent&>(event);

		if (!imguiConsumingMouse && e.getCode() == Aquarius::Input::MouseButtonCode::Mouse_button_1)
		{
			placeActiveItem();
		}
	}

	void setMovespeed(float speed)
	{
		m_moveSpeed = speed;
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

	std::unordered_map<std::string, std::vector<Item*>> m_inventory;
	std::vector<std::string> m_itemTypes;
	std::vector<std::string>::iterator m_activeItemIt;
	Level* m_level;
};
