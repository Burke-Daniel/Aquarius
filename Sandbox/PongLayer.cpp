#include "PongLayer.h"

#include "Aquarius.h"

#include <array>
#include <cmath>

static constexpr auto bottomLeft = 0;
static constexpr auto bottomRight = 1;
static constexpr auto topRight = 2;
static constexpr auto topLeft = 3;
static constexpr auto x = 0;
static constexpr auto y = 1;
static constexpr auto pi = 3.14159265358979323846;


PongLayer::PongLayer()
	: Layer("Pong"), m_LeftPaddle(), m_RightPaddle()
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

	m_LeftPaddle = {
		std::make_unique<KeyboardPaddleController>(Aquarius::Input::KeyCode::Key_w, Aquarius::Input::KeyCode::Key_s),
		{ 20.0, (window.getHeight() / 2.0) - 40.0},
		{ 10.0, 80.0 },
		0.3
	};

	m_RightPaddle = {
		std::make_unique<AIPaddleController>(),
		{ window.getWidth() - 30.0, (window.getHeight() / 2.0) - 40.0 },
		{ 10.0, 80.0 },
		0.2
	};

	m_Ball = {
		{ (window.getWidth() / 2.0) - 5.0, (window.getHeight() / 2.0) - 5.0 },
		{ 10, 10 },
		{ 0.4, 0.4 },
		{ -0.2, 0.0 }
	};
}

void PongLayer::onEvent(const Aquarius::Event& event)
{
	auto keyPressEvent = static_cast<const Aquarius::KeyPressedEvent&>(event);
	switch (keyPressEvent.getCode())
	{
		case(Aquarius::Input::KeyCode::Key_escape):
		{
			active = !active;
			break;
		}
	}
}

void PongLayer::onUpdate(Aquarius::timeDelta_t dt)
{
	if (active)
	{
		Aquarius::Application* app = Aquarius::Application::get();
		Aquarius::Window* window = app->getWindow();

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
	// Starting at bottom left, going counter-clockwise
	float leftPaddleCoords[4][2] = {
		{ m_LeftPaddle.position.x, m_LeftPaddle.position.y + m_LeftPaddle.size.y },
		{ m_LeftPaddle.position.x + m_LeftPaddle.size.x, m_LeftPaddle.position.y + m_LeftPaddle.size.y },
		{ m_LeftPaddle.position.x + m_LeftPaddle.size.x, m_LeftPaddle.position.y },
		{ m_LeftPaddle.position.x, m_LeftPaddle.position.y}
	};

	float rightPaddleCoords[4][2] = {
		{ m_RightPaddle.position.x, m_RightPaddle.position.y + m_RightPaddle.size.y },
		{ m_RightPaddle.position.x + m_RightPaddle.size.x, m_RightPaddle.position.y + m_RightPaddle.size.y },
		{ m_RightPaddle.position.x + m_RightPaddle.size.x, m_RightPaddle.position.y },
		{ m_RightPaddle.position.x, m_RightPaddle.position.y}
	};

	float ballCoords[4][2] = {
		{ m_Ball.position.x, m_Ball.position.y + m_Ball.size.y },
		{ m_Ball.position.x + m_Ball.size.x, m_Ball.position.y + m_Ball.size.y },
		{ m_Ball.position.x + m_Ball.size.x, m_Ball.position.y },
		{ m_Ball.position.x, m_Ball.position.y}
	};

	// Check Collision with right paddle

	if (ballCoords[topRight][x] >= rightPaddleCoords[topLeft][x])
	{
		if (ballCoords[topRight][y] >= rightPaddleCoords[topLeft][y] &&
			ballCoords[topRight][y] <= rightPaddleCoords[bottomLeft][y])
		{
			AQ_INFO("Collision with right paddle!!");
			handleCollision(false);
		}
	}

	if (ballCoords[topLeft][x] <= leftPaddleCoords[topRight][x])
	{
		if (ballCoords[topLeft][y] >= leftPaddleCoords[topRight][y] &&
			ballCoords[topLeft][y] <= leftPaddleCoords[bottomRight][y])
		{
			AQ_INFO("Collision with left paddle!!");
			handleCollision(true);
		}
	}
}

void PongLayer::handleCollision(bool isLeftPaddle)
{
	if (isLeftPaddle)
	{
		auto relativeIntersectY = (m_LeftPaddle.position.y + (m_LeftPaddle.size.y / 2.0)) - (m_Ball.position.y + (m_Ball.size.y / 2.0));
		auto normalizedIntersectY = relativeIntersectY / (m_LeftPaddle.size.y / 2.0);
		
		// TODO make departure angle configurable
		auto bounceAngle = normalizedIntersectY * 45.0;
		m_Ball.velocity = { m_Ball.speed.x * cos(bounceAngle * (pi / 180.0)), -m_Ball.speed.y * sin(bounceAngle * (pi / 180.0)) };
		m_Ball.speed = { m_Ball.speed.x + 0.02, m_Ball.speed.y };
	}

	else
	{
		auto relativeIntersectY = (m_RightPaddle.position.y + (m_RightPaddle.size.y / 2.0)) - (m_Ball.position.y + (m_Ball.size.y / 2.0));
		auto normalizedIntersectY = relativeIntersectY / (m_RightPaddle.size.y / 2.0);

		// TODO make departure angle configurable
		auto bounceAngle = normalizedIntersectY * 75.0;
		m_Ball.velocity = { -m_Ball.speed.x * cos(bounceAngle * (pi / 180.0)), -m_Ball.speed.y * sin(bounceAngle * (pi / 180.0)) };
		m_Ball.speed = { m_Ball.speed.x + 0.02, m_Ball.speed.y };
	}
}
