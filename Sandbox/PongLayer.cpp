#include "PongLayer.h"

#include "Aquarius.h"

#include <array>
#include <cmath>


static constexpr auto pi = 3.14159265358979323846;

PongLayer::PongLayer()
	: Layer("Pong", true), m_LeftPaddle(), m_RightPaddle(), m_Ball()
{
	app.getEventHandler().subscribe(Aquarius::eventType::KeyPressedEvent,
		[&](const Aquarius::Event& event)
		{
			onEvent(event);
		});
}

void PongLayer::onCreation()
{
	int height = window.getHeight();
	int width = window.getWidth();

	m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);
	Aquarius::Renderer::Init();

	constexpr auto paddleWidth = 10.0;
	constexpr auto paddleHeight = 80.0;
	constexpr auto ballSize = 10.0;
	constexpr auto leftPaddleSpeed = 0.3;
	constexpr auto rightPaddleSpeed = 0.2;

	m_LeftPaddle = {
		std::make_unique<KeyboardPaddleController>(Aquarius::Input::KeyCode::Key_w, Aquarius::Input::KeyCode::Key_s),
		{ 20.0, (window.getHeight() / 2.0) - 40.0},
		{ paddleWidth, paddleHeight },
		leftPaddleSpeed
	};

	m_RightPaddle = {
		std::make_unique<AIPaddleController>(),
		{ window.getWidth() - 30.0, (window.getHeight() / 2.0) - 40.0 },
		{ paddleWidth, paddleHeight },
		rightPaddleSpeed
	};

	m_Ball = {
		{ (window.getWidth() / 2.0) - 5.0, (window.getHeight() / 2.0) - 5.0 },
		{ ballSize, ballSize },
		{ 0.4, 0.4 },
		{ -0.2, 0.0 },
		this
	};
}

void PongLayer::onEvent(const Aquarius::Event& event)
{
	// Static cast instead of dynamic because we know this will be a KeyPressedEvent
	// no need for a runtime check
	auto keyPressEvent = static_cast<const Aquarius::KeyPressedEvent&>(event);
	switch (keyPressEvent.getCode())
	{
		case(Aquarius::Input::KeyCode::Key_escape):
		{
			isActive() ? deactivate() : activate();
			break;
		}
	}
}

void PongLayer::onUpdate(Aquarius::timeDelta_t dt)
{
	if (isActive())
	{
		Aquarius::Renderer::BeginScene(m_Camera.get());
		Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
		Aquarius::Renderer::Clear();

		float dy = dt * m_LeftPaddle.speedY;

		m_RightPaddle.controller->movePaddle(dt, &m_RightPaddle, &m_Ball);
		m_LeftPaddle.controller->movePaddle(dt, &m_LeftPaddle, &m_Ball);

		m_Ball.Update(dt);
		checkPaddleCollision();

		m_LeftPaddle.Render();
		m_RightPaddle.Render();
		m_Ball.Render();
	}
}

void PongLayer::checkPaddleCollision()
{
	// Constants for readability
	static constexpr auto bottomLeft = 0;
	static constexpr auto bottomRight = 1;
	static constexpr auto topRight = 2;
	static constexpr auto topLeft = 3;

	// Starting at bottom left, going counter-clockwise
	std::array<glm::vec2, 4> leftPaddleCoords = {
		glm::vec2{ m_LeftPaddle.position.x, m_LeftPaddle.position.y + m_LeftPaddle.size.y },
		glm::vec2{ m_LeftPaddle.position.x + m_LeftPaddle.size.x, m_LeftPaddle.position.y + m_LeftPaddle.size.y },
		glm::vec2{ m_LeftPaddle.position.x + m_LeftPaddle.size.x, m_LeftPaddle.position.y },
		glm::vec2{ m_LeftPaddle.position.x, m_LeftPaddle.position.y }
	};

	std::array<glm::vec2, 4> rightPaddleCoords = {
		glm::vec2{ m_RightPaddle.position.x, m_RightPaddle.position.y + m_RightPaddle.size.y },
		glm::vec2{ m_RightPaddle.position.x + m_RightPaddle.size.x, m_RightPaddle.position.y + m_RightPaddle.size.y },
		glm::vec2{ m_RightPaddle.position.x + m_RightPaddle.size.x, m_RightPaddle.position.y },
		glm::vec2{ m_RightPaddle.position.x, m_RightPaddle.position.y }
	};

	std::array<glm::vec2, 4> ballCoords = {
		glm::vec2{ m_Ball.position.x, m_Ball.position.y + m_Ball.size.y },
		glm::vec2{ m_Ball.position.x + m_Ball.size.x, m_Ball.position.y + m_Ball.size.y },
		glm::vec2{ m_Ball.position.x + m_Ball.size.x, m_Ball.position.y },
		glm::vec2{ m_Ball.position.x, m_Ball.position.y }
	};

	// Check Collision with right paddle
	if (ballCoords[topRight].x >= rightPaddleCoords[topLeft].x)
	{
		if (ballCoords[topRight].y >= rightPaddleCoords[topLeft].y &&
			ballCoords[topRight].y <= rightPaddleCoords[bottomLeft].y)
		{
			AQ_INFO("Collision with right paddle!!");
			handleCollision(false);
		}
	}

	if (ballCoords[topLeft].x <= leftPaddleCoords[topRight].x)
	{
		if (ballCoords[topLeft].y >= leftPaddleCoords[topRight].y &&
			ballCoords[topLeft].y <= leftPaddleCoords[bottomRight].y)
		{
			AQ_INFO("Collision with left paddle!!");
			handleCollision(true);
		}
	}
}

void PongLayer::handleCollision(bool isLeftPaddle)
{
	constexpr auto maxDepartureAngle = 45.0;

	// This weird looking calculation gives the ball a departure angle
	// based off of how far away from the centre of the paddle the collision
	// takes place. For example, if the ball collides exactly in the middle of the
	// paddle, the departure angle will be zero degrees (horizontal)
	if (isLeftPaddle)
	{
		auto relativeIntersectY = (m_LeftPaddle.position.y + (m_LeftPaddle.size.y / 2.0)) - (m_Ball.position.y + (m_Ball.size.y / 2.0));
		auto normalizedIntersectY = relativeIntersectY / (m_LeftPaddle.size.y / 2.0);
		
		auto bounceAngle = normalizedIntersectY * maxDepartureAngle;
		m_Ball.velocity = { m_Ball.speed.x * cos(bounceAngle * (pi / 180.0)), -m_Ball.speed.y * sin(bounceAngle * (pi / 180.0)) };
		m_Ball.speed = { m_Ball.speed.x + 0.02, m_Ball.speed.y };
	}

	else
	{
		auto relativeIntersectY = (m_RightPaddle.position.y + (m_RightPaddle.size.y / 2.0)) - (m_Ball.position.y + (m_Ball.size.y / 2.0));
		auto normalizedIntersectY = relativeIntersectY / (m_RightPaddle.size.y / 2.0);

		auto bounceAngle = normalizedIntersectY * maxDepartureAngle;
		m_Ball.velocity = { -m_Ball.speed.x * cos(bounceAngle * (pi / 180.0)), -m_Ball.speed.y * sin(bounceAngle * (pi / 180.0)) };
		m_Ball.speed = { m_Ball.speed.x + 0.02, m_Ball.speed.y };
	}
}

