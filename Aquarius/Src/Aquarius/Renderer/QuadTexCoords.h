#pragma once

#include <array>
#include <glm/glm.hpp>


namespace Aquarius {

	// Class representing quad renderer texture coords 
	// Bottom left, bottom right, top right, top left
	class QuadTexCoords
	{
	public: 
		QuadTexCoords()
			: m_data(std::array<glm::vec2, 4>{ glm::vec2{ 0, 0 },
											   glm::vec2{ 0, 0 },
											   glm::vec2{ 0, 0 },
											   glm::vec2{ 0, 0 } })
		{}
		QuadTexCoords(std::array<glm::vec2, 4> data) : m_data(data) {}
		~QuadTexCoords() = default;

		glm::vec2 botLeft() const { return m_data[0]; }
		glm::vec2 botRight() const { return m_data[1]; }
		glm::vec2 topRight() const { return m_data[2]; }
		glm::vec2 topLeft() const { return m_data[3]; }

		QuadTexCoords getFlipped() const 
		{ 
			return QuadTexCoords
			( 
				std::array<glm::vec2, 4> 
				(
					{
						topLeft(),
						topRight(),
						botRight(),
						botLeft(),
					}
				)
			); 
		}

	private:
		std::array<glm::vec2, 4> m_data;
	};
	
} // namespace Aquarius
