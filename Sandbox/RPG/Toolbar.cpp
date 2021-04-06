#include "Toolbar.h"

void Toolbar::draw() const
{
	// Draw background
	Aquarius::Renderer::DrawQuad(
		m_position,
		m_size,
		0,
		{0.71, 0.396, 0.11, 0.95}
	);

	// Draw item sprite, smaller and offset by 10
	if (m_activeItemTexCoords != nullptr)
	{
		Aquarius::Renderer::DrawQuad(
			{ m_position.x + 10, m_position.y + 10 },
			{ m_size.x - 10, m_size.y - 10 },
			m_activeItemIcon,
			m_activeItemTexCoords
		);
	}
}

void Toolbar::setActiveItemIcon(Aquarius::Texture* texture, Aquarius::QuadTexCoords* texCoords)
{
	m_activeItemIcon = texture;
	m_activeItemTexCoords = texCoords;
}

void Toolbar::setAlignment(ToolbarAlignment alignment)
{
	m_alignment = alignment;

	Aquarius::Application* app = Aquarius::Application::get();
	int screenW = app->getWindow()->getWidth();
	int screenH = app->getWindow()->getHeight();

	switch (m_alignment)
	{
		case ToolbarAlignment::TopLeft:
			m_position = {0, 0};
			break;
		case ToolbarAlignment::TopRight:
			m_position = { screenW - m_size.x, 0 };
			break;
		case ToolbarAlignment::BottomLeft:
			m_position = {0, screenH - m_size.y};
			break;
		case ToolbarAlignment::BottomRight:
			m_position = { screenW - m_size.x, screenH - m_size.y };
			break;
		case ToolbarAlignment::TopCenter:
			m_position = { (screenW / 2) - (m_size.x / 2), 0 };
			break;
		case ToolbarAlignment::BottomCenter:
			m_position = { (screenW / 2) - (m_size.x / 2), screenH - m_size.y };
			break;
	}
}
