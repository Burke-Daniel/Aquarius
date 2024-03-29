#include "Ball.h"

#include "../PongLayer.h"


void Ball::Render() const
{
	Aquarius::Renderer::DrawQuad(
		position,
		size,
		ballTexture.get()
	);
}

void Ball::Update(Aquarius::timeDelta_t dt)
{
	Aquarius::Application* app = Aquarius::Application::get();
	Aquarius::Window* window = app->getWindow();

	int height = window->getHeight();
	int width = window->getWidth();
	auto dx = dt * velocity.x;
	auto dy = dt * velocity.y;
	
	position.x += dx;
	position.y += dy;

	if (position.y <= 0 || position.y >= window->getHeight() - 10.0)
	{
		position.y -= dy;
		velocity.y = -velocity.y;
	}

	if (position.x <= 0)
	{
		AQ_INFO("Right Paddle Scored!");
		game->rightScore();
		auto score = game->getScore();
		AQ_INFO("Current Score: %v - %v", (int)score.LeftScore, (int)score.RightScore);
		Reset(false);
	}

	if (position.x >= window->getWidth() + 10.0)
	{
		AQ_INFO("Left Paddle Scored!");
		game->leftScore();
		auto score = game->getScore();
		AQ_INFO("Current Score: %v - %v", (int)score.LeftScore, (int)score.RightScore);
		Reset(true);
	}
}

void Ball::Reset(bool leftScored)
{
	static float yVelocity = 0.2;
	Aquarius::Application* app = Aquarius::Application::get();
	Aquarius::Window* window = app->getWindow();

	yVelocity = -yVelocity;
	// TODO Randomize starting velocity
	position = { (window->getWidth() / 2.0) - 5.0, (window->getHeight() / 2.0) - 5.0 };
	velocity = { leftScored ? 0.2 : -0.2, yVelocity };
	speed = { 0.4, 0.4 };
}
