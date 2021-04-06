#include "PongLayer.h"

#include "Aquarius.h"

#include <algorithm>
#include <array>
#include <cmath>


static constexpr auto pi = 3.14159265358979323846;

static const struct
{
	const float RegularMode = 0.02;
	const float HyperMode = 0.5;
} GameMode {};

static auto ballSpeedIncrease = GameMode.RegularMode;

PongLayer::PongLayer()
	: Layer("Pong", true), m_LeftPaddle(), m_RightPaddle(), m_Ball()
{
	app.getEventHandler().subscribe(Aquarius::eventType::KeyPressedEvent,
		[&](const Aquarius::Event& event)
		{
			onEvent(event);
		});

	app.getEventHandler().subscribe(Aquarius::eventType::WindowResizedEvent,
		[&](const Aquarius::Event& event)
		{
			auto windowResize = static_cast<const Aquarius::WindowResizedEvent&>(event);
			m_RightPaddle.position = glm::vec2(window.getWidth() - 30.0, (window.getHeight() / 2.0) - 40.0);
		});
}

PongLayer::~PongLayer()
{
	onDestruction();
}

void PongLayer::onCreation()
{
	int height = window.getHeight();
	int width = window.getWidth();

	m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);
	Aquarius::Renderer::Init();

	constexpr auto paddleWidth = 10.0;
	constexpr auto paddleHeight = 80.0;
	constexpr auto ballSize = 15.0;
	constexpr auto leftPaddleSpeed = 0.3;
	constexpr auto rightPaddleSpeed = 0.2;

	Aquarius::TextureConfiguration textureConfiguration = {
		Aquarius::TextureWrapOption::Repeat,
		Aquarius::TextureWrapOption::Repeat,
		Aquarius::TextureFilteringOption::Nearest,
		Aquarius::TextureFilteringOption::Nearest,
	};

	auto paddleTexture = std::make_shared<Aquarius::Texture>("Sandbox/Assets/Paddle.png", textureConfiguration, true);
	auto ballTexture = std::make_shared<Aquarius::Texture>("Sandbox/Assets/Ball.png", textureConfiguration, true);
	m_BackgroundTexture = std::make_shared<Aquarius::Texture>("Sandbox/Assets/logo-black-transparent.png", Aquarius::TextureConfiguration{}, true);
	m_FontTexture = std::make_shared<Aquarius::Texture>("Sandbox/Assets/8bitfont.png", textureConfiguration, true);
	m_Font = std::make_shared<Aquarius::Bitmap>(m_FontTexture.get(), 21, 28);

	m_SoundBuffer = Aquarius::Sound::SoundBuffer::Create();
    m_PaddleSound = m_SoundBuffer->addEffect("Sandbox/Assets/Paddle-sound.wav");

	m_LeftPaddle = {
		paddleTexture,
		//std::make_unique<MousePaddleController>(),
		std::make_unique<KeyboardPaddleController>(Aquarius::Input::KeyCode::Key_w, Aquarius::Input::KeyCode::Key_s),
		//std::make_unique<AIPaddleController>(),
		{ 20.0, (window.getHeight() / 2.0) - 40.0},
		{ paddleWidth, paddleHeight },
		leftPaddleSpeed
	};

	m_RightPaddle = {
		paddleTexture,
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
		this,
		ballTexture
	};

	m_SoundSource.beginSoundThread();
}

void PongLayer::onEvent(const Aquarius::Event& event)
{
	if (isActive())
	{
		// Static cast instead of dynamic because we know this will be a KeyPressedEvent
		// no need for a runtime check
		auto keyPressEvent = static_cast<const Aquarius::KeyPressedEvent&>(event);
		switch (keyPressEvent.getCode())
		{
			case(Aquarius::Input::KeyCode::Key_p):
			{
				m_isPaused = !m_isPaused;
				break;
			}

			case(Aquarius::Input::KeyCode::Key_h):
			{
				if (ballSpeedIncrease == GameMode.RegularMode)
				{
					ballSpeedIncrease = GameMode.HyperMode;
					AQ_INFO("HYPER MODE ACTIVATED!!!");
				}
				else
				{
					ballSpeedIncrease = GameMode.RegularMode;
				}
				break;
			}
		}
	}
}

void PongLayer::onUpdate(Aquarius::timeDelta_t dt)
{
	Aquarius::Renderer::BeginScene(m_Camera.get());
	Aquarius::Renderer::ClearColor({ 169.0 / 255.0, 169.0 / 255.0, 169.0 / 255.0 });
	Aquarius::Renderer::Clear();

	float dy = dt * m_LeftPaddle.speedY;

	if (!m_isPaused)
	{
		m_RightPaddle.controller->movePaddle(dt, &m_RightPaddle, &m_Ball);
		m_LeftPaddle.controller->movePaddle(dt, &m_LeftPaddle, &m_Ball);

		m_Ball.Update(dt);
		checkPaddleCollision();
	}

	Aquarius::Renderer::DrawQuad(
		{ 0.0, 0.0 },
		{ window.getWidth(), window.getHeight() },
		m_BackgroundTexture.get()
	);

	char leftScore[3];
	char rightScore[3];
	sprintf(leftScore, "%02d", m_Score.LeftScore);
	sprintf(rightScore, "%02d", m_Score.RightScore);
	
	glm::vec4 red = { 1.0, 0.0, 0.0, 1.0 };
	
	// To center the scoreboard position, subtract 2.5 times the sprite width (scoreboard contains 5 sprites)
	// and then multiply by 2.0 because of the multiplier on the font size in the RenderText call
	glm::vec2 scoreboardPosition = { (window.getWidth() / 2.0) - (m_Font->getSpriteWidth() * 2.0 * 2.5), 20.0 };

	m_Font->RenderText(std::string(leftScore) + "-" + std::string(rightScore), scoreboardPosition, 2.0, red);
	
	m_LeftPaddle.Render();
	m_RightPaddle.Render();
	m_Ball.Render();

	AQ_TRACE("Frametime: %v ms", dt);
	AQ_TRACE("FPS: %v", 1000 / dt);
}

void PongLayer::onDestruction()
{
	m_SoundSource.endSoundThread();
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
	if (ballCoords[topRight].x >= rightPaddleCoords[topLeft].x &&
		ballCoords[topRight].x <= rightPaddleCoords[topRight].x)
	{
		if ((ballCoords[topRight].y >= rightPaddleCoords[topLeft].y &&
			ballCoords[topRight].y <= rightPaddleCoords[bottomLeft].y) ||
		   (ballCoords[bottomRight].y >= rightPaddleCoords[topLeft].y &&
			ballCoords[bottomRight].y <= rightPaddleCoords[bottomLeft].y))
		{
		    m_SoundSource.queueSound(m_PaddleSound, m_Gain);
			AQ_INFO("Collision with right paddle!!");
			handleCollision(false);
		}
	}

	if (ballCoords[topLeft].x <= leftPaddleCoords[topRight].x &&
		ballCoords[topLeft].x >= leftPaddleCoords[topLeft].x)
	{
		if ((ballCoords[topLeft].y >= leftPaddleCoords[topRight].y &&
			ballCoords[topLeft].y <= leftPaddleCoords[bottomRight].y) ||
		   (ballCoords[bottomLeft].y >= leftPaddleCoords[topRight].y &&
			ballCoords[bottomLeft].y <= leftPaddleCoords[bottomRight].y))
		{
            m_SoundSource.queueSound(m_PaddleSound, m_Gain);
			AQ_INFO("Collision with left paddle!!");
			handleCollision(true);
		}
	}
}

void PongLayer::handleCollision(bool isLeftPaddle)
{
	constexpr auto maxDepartureAngle = 45.0;
	constexpr float maxBallSpeed = 1.75;

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
		m_Ball.speed = { std::min(m_Ball.speed.x + ballSpeedIncrease, maxBallSpeed), m_Ball.speed.y };
	}

	else
	{
		auto relativeIntersectY = (m_RightPaddle.position.y + (m_RightPaddle.size.y / 2.0)) - (m_Ball.position.y + (m_Ball.size.y / 2.0));
		auto normalizedIntersectY = relativeIntersectY / (m_RightPaddle.size.y / 2.0);

		auto bounceAngle = normalizedIntersectY * maxDepartureAngle;
		m_Ball.velocity = { -m_Ball.speed.x * cos(bounceAngle * (pi / 180.0)), -m_Ball.speed.y * sin(bounceAngle * (pi / 180.0)) };
		m_Ball.speed = { std::min(m_Ball.speed.x + ballSpeedIncrease, maxBallSpeed), m_Ball.speed.y };
	}
}

