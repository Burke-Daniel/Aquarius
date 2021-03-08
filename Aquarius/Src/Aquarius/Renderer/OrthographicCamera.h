#pragma once

#include "Aquarius/Core/Input.h"
#include "Aquarius/Core/Utility.h"
#include "Aquarius/Core/Log.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Aquarius {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float moveSpeed, float left, float right, float bot, float top)
		{
			m_Position = glm::vec3(0.0f, 0.0f, 1.0f);
			m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
			m_moveSpeed = moveSpeed;
			m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
			
			updateView();
			updateProjection(left, right, bot, top);
		}

		~OrthographicCamera() = default;

		void onUpdate(timeDelta_t dt)
		{
			// Delta pos = time * speed (no accel yet)
			float dx = dt * m_moveSpeed;

			// TODO - Why
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

			// TODO - figure out zoom
			if (Input::isKeyPressed(Input::KeyCode::Key_down))
			{
				m_Position.z += dx;
			}

			if (Input::isKeyPressed(Input::KeyCode::Key_up))
			{
				m_Position.z -= dx;

			}

			updateView();
		}

		// TODO - Recalculate projection on window resize
		// TODO - Recalculate view on scroll (slide camera back along the z axis)
		void onEvent(); 


		void updateView() 
		{ 
			// Eye, center, up
			m_View = glm::lookAt(m_Position, 
								 m_Position + m_cameraFront,
								 m_Up);
		}

		
		void updateProjection(float left, float right, float bottom, float top, float nearClip=-1.0f, float farClip=1.0f)
		{
			m_Projection = glm::ortho(left, right, bottom, top, nearClip, farClip);
		}

		const glm::mat4& getView() const { return m_View; };
		const glm::mat4& getProjection() const { return m_Projection; }
		const glm::vec3& getPosition() const { return m_Position; }
		void setPosition(const glm::vec3& pos) { m_Position = pos; }

	private:
		glm::vec3 m_Up;
		glm::vec3 m_Position;
		glm::vec3 m_cameraFront;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
		float m_moveSpeed;
	};

} // namespace Aquarius
