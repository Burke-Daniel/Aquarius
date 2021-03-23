#pragma once

#include "Aquarius.h"

struct Ball;
struct Paddle;


void moveUp(Aquarius::timeDelta_t dt, Paddle* paddle);
void moveDown(Aquarius::timeDelta_t dt, Paddle* paddle);

class PaddleController
{
public:
	virtual ~PaddleController() {};
	virtual void movePaddle(Aquarius::timeDelta_t dt, Paddle* paddle = nullptr, Ball* ball = nullptr) = 0;
};

class KeyboardPaddleController : public PaddleController
{
public:
	KeyboardPaddleController(Aquarius::Input::KeyCode, Aquarius::Input::KeyCode);
	void movePaddle(Aquarius::timeDelta_t dt, Paddle* paddle = nullptr, Ball* ball = nullptr) override;

private:
	Aquarius::Input::KeyCode m_UpKey;
	Aquarius::Input::KeyCode m_DownKey;
};

class MousePaddleController : public PaddleController
{
public:
	void movePaddle(Aquarius::timeDelta_t dt, Paddle* paddle = nullptr, Ball* ball = nullptr) override;
};

class AIPaddleController : public PaddleController
{
public:
	void movePaddle(Aquarius::timeDelta_t dt, Paddle* paddle = nullptr, Ball* ball = nullptr) override;
};
