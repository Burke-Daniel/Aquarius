#include "PongLayer.h"

#include "Aquarius/Renderer/Renderer.h"

void Paddle::Render()
{
	Aquarius::Renderer::DrawQuad(
		position,
		size,
		0,
		{ 1.0, 0.5, 1.0, 1.0 }
	);
}

void Paddle::moveUp(Aquarius::timeDelta_t dt)
{
	if (position.y > 0)
	{
		auto dy = dt * speedY;
		position.y -= dy;
	}
}

void Paddle::moveDown(Aquarius::timeDelta_t dt)
{
	if (position.y < Aquarius::Application::get()->getWindow()->getHeight() - 80.0)
	{
		auto dy = dt * speedY;
		position.y += dy;
	}
}

PongLayer::PongLayer()
	: Layer("Pong"), m_LeftPaddle(), m_RightPaddle()
{}

void PongLayer::onCreation()
{
	Aquarius::Application* app = Aquarius::Application::get();
	Aquarius::Window* window = app->getWindow();

	int height = window->getHeight();
	int width = window->getWidth();

	m_Camera = std::make_shared<Aquarius::OrthographicCamera>(1, 0.01, height, width);
	Aquarius::Renderer::Init();

	m_LeftPaddle = { { 20.0, (window->getHeight() / 2.0) - 40.0}, { 10.0, 80.0 }, 1.0, };
	m_RightPaddle = { { window->getWidth() - 30.0, (window->getHeight() / 2.0) - 40.0 }, { 10.0, 80.0 }, 1.0 };
}

void PongLayer::onEvent(const Aquarius::Event& event)
{
}

void PongLayer::onUpdate(Aquarius::timeDelta_t dt)
{
	Aquarius::Application* app = Aquarius::Application::get();
	Aquarius::Window* window = app->getWindow();

	Aquarius::Renderer::BeginScene(m_Camera.get());
	Aquarius::Renderer::ClearColor({ 0.2, 0.3, 0.7 });
	Aquarius::Renderer::Clear();

	float dy = dt * m_LeftPaddle.speedY;

	if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_w))
	{
		m_LeftPaddle.moveUp(dt);
	}

	if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_s))
	{
		m_LeftPaddle.moveDown(dt);
	}

	if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_up))
	{
		m_RightPaddle.moveUp(dt);
	}

	if (Aquarius::Input::isKeyPressed(Aquarius::Input::KeyCode::Key_down))
	{
		m_RightPaddle.moveDown(dt);
	}

	m_LeftPaddle.Render();
	m_RightPaddle.Render();

	Aquarius::Renderer::DrawQuad(
		{ (window->getWidth() / 2.0) - 5.0, (window->getHeight() / 2.0) - 5.0 },
		{ 10, 10 },
		0,
		{ 1.0, 0.5, 1.0, 1.0 });

}