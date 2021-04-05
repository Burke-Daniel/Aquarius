#pragma once

#include "Aquarius/Core/Input.h"
#include "Aquarius/Core/Utility.h"
#include "Aquarius/Core/Log.h"
#include "Aquarius/Events/Event.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Aquarius {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float moveSpeed, float zoomSpeed, float height, float width);
		~OrthographicCamera() = default;

		void onUpdate(timeDelta_t dt);
		void onWindowResize(const Event& event);
		void updateView();
		void updateProjection();

		void setPosition(const glm::vec3& pos) { m_Position = pos; updateView(); }
		void setZoom(float zoom) { m_Zoom = zoom; updateView(); }
		float getZoom() const { return m_Zoom; }
		const glm::mat4& getView() const { return m_View; };
		const glm::mat4& getProjection() const { return m_Projection; }
		const glm::vec3& getPosition() const { return m_Position; }
	private:
		glm::vec3 m_Up;
		glm::vec3 m_Position;
		glm::vec3 m_cameraFront;
		glm::mat4 m_View;
		glm::mat4 m_Projection;
		float m_moveSpeed;
		float m_Zoom;
		float m_ZoomSpeed;
		float m_Height;
		float m_Width;
	};

} // namespace Aquarius
