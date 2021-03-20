#include "PaddleController.h"

#include "Ball.h"
#include "Paddle.h"


void moveUp(Aquarius::timeDelta_t dt, Paddle* paddle)
{
	if (paddle->position.y > 0)
	{
		auto dy = dt * paddle->speedY;
		paddle->position.y -= dy;
	}
}

void moveDown(Aquarius::timeDelta_t dt, Paddle* paddle)
{
	if (paddle->position.y < Aquarius::Application::get()->getWindow()->getHeight() - 80.0)
	{
		auto dy = dt * paddle->speedY;
		paddle->position.y += dy;
	}
}

KeyboardPaddleController::KeyboardPaddleController(Aquarius::Input::KeyCode upKey, Aquarius::Input::KeyCode downKey)
	: m_UpKey(upKey), m_DownKey(downKey)
{}

void KeyboardPaddleController::movePaddle(Aquarius::timeDelta_t dt, Paddle* paddle, Ball* ball)
{
	if (Aquarius::Input::isKeyPressed(m_UpKey))
	{
		moveUp(dt, paddle);
	}

	if (Aquarius::Input::isKeyPressed(m_DownKey))
	{
		moveDown(dt, paddle);
	}
}

void MousePaddleController::movePaddle(Aquarius::timeDelta_t dt, Paddle* paddle, Ball* ball)
{
	if (Aquarius::Input::getMousePosition().y > (paddle->position.y + (paddle->size.y / 2.0)))
	{
		moveDown(dt, paddle);
	}

	if (Aquarius::Input::getMousePosition().y < (paddle->position.y + (paddle->size.y / 2.0)))
	{
		moveUp(dt, paddle);
	}
}

void AIPaddleController::movePaddle(Aquarius::timeDelta_t dt, Paddle* paddle, Ball* ball)
{
	if (paddle->position.y + (paddle->size.y / 2.0) > ball->position.y + (ball->size.y / 2.0))
	{
		moveUp(dt, paddle);
	}
	else if (paddle->position.y + (paddle->size.y / 2.0) < ball->position.y + (ball->size.y / 2.0))
	{
		moveDown(dt, paddle);
	}
}
