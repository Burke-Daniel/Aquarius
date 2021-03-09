#include "OrthographicCamera.h"

namespace Aquarius {

	OrthographicCamera::OrthographicCamera(float moveSpeed, float zoomSpeed, float height, float width)
		: m_Up{ 0, 1, 0 }, 
		  m_Position{ 0, 0, -1 }, 
		  m_cameraFront{ 0, 0, -1 },
		  m_moveSpeed(moveSpeed),
		  m_Zoom(1),
		  m_ZoomSpeed(zoomSpeed),
		  m_Height(height),
		  m_Width(width)
	{
		updateView();
		updateProjection();
	}

	void OrthographicCamera::onUpdate(timeDelta_t dt)
	{
		// Delta position 
		float dx = dt * m_moveSpeed;
		float dzoom = dt * 0.1 * m_ZoomSpeed;

		// Up
		if (Input::isKeyPressed(Input::KeyCode::Key_w))
		{
			m_Position.y -= dx;;
		}

		// Down
		if (Input::isKeyPressed(Input::KeyCode::Key_s))
		{
			m_Position.y += dx;
		}

		// Left
		if (Input::isKeyPressed(Input::KeyCode::Key_a))
		{
			m_Position.x -= dx;
		}

		// Right
		if (Input::isKeyPressed(Input::KeyCode::Key_d))
		{
			m_Position.x += dx;
		}

		// Zoom 
		if (Input::isKeyPressed(Input::KeyCode::Key_down))
		{
			m_Zoom = m_Zoom - dzoom;
		}

		if (Input::isKeyPressed(Input::KeyCode::Key_up))
		{
			m_Zoom += dzoom;
		}

		// Clamp zoom > 0.1
		m_Zoom = m_Zoom > 0.1 ? m_Zoom : 0.1;

		updateView();
		updateProjection();
	}

	void OrthographicCamera::updateView()
	{
		// Eye, center, up
		m_View = glm::lookAt(m_Position,
							 m_Position + m_cameraFront,
							 m_Up);

		// Shift to center of screen, then to camera location, then scale, and finally translate back to origin
		m_View = glm::translate(m_View, { m_Width / 2.0f + m_Position.x, m_Height / 2.0f + m_Position.y, 0.0f });
		m_View = glm::scale(m_View, { m_Zoom, m_Zoom, 1 });
		m_View = glm::translate(m_View, { -(m_Width / 2.0f + m_Position.x), -(m_Height / 2.0f + m_Position.y), 0.0f });
	}

	void OrthographicCamera::updateProjection()
	{
		m_Projection = glm::ortho(0.0f, m_Width, m_Height, 0.0f, -1.0f, 1.0f);
	}

} // namespace Aquarius
