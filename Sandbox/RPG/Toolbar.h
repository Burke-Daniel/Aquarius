#pragma once
#include "Aquarius.h"


enum class ToolbarAlignment
{
	TopLeft,
	TopRight,
	BottomRight,
	BottomLeft,
	BottomCenter,
	TopCenter
};

class Toolbar
{
public:
	Toolbar(glm::vec2 size, 
		    Aquarius::Texture* texture,
		    Aquarius::QuadTexCoords* texCoords)
		: m_position({0,0}),
		  m_size(size),
		  m_activeItemIcon(texture), 
		  m_activeItemTexCoords(texCoords),
		  m_alignment(ToolbarAlignment::TopLeft) 
	{};

	~Toolbar() = default;

	void draw() const;
	void setActiveItemIcon(Aquarius::Texture* texture, Aquarius::QuadTexCoords* texCoords);
	void setAlignment(ToolbarAlignment alignment);
	void setColor(const glm::vec4& color);

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
	Aquarius::Texture* m_activeItemIcon;
	Aquarius::QuadTexCoords* m_activeItemTexCoords;
	ToolbarAlignment m_alignment;
	glm::vec4 m_color = { 0, 0, 0, 1 };
};