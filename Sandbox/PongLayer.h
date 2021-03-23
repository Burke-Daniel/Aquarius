#pragma once

#include "Aquarius.h"

#include "Pong/Ball.h"
#include "Pong/Paddle.h"
#include "Pong/PaddleController.h"


struct Score
{
	uint8_t RightScore;
	uint8_t LeftScore;
};

class PongLayer : public Aquarius::Layer
{
public:
	PongLayer();

	void onCreation() override;
	void onEvent(const Aquarius::Event&) override;
	void onUpdate(Aquarius::timeDelta_t) override;

	void leftScore() { score.LeftScore++; }
	void rightScore() { score.RightScore++; }
	Score getScore() const { return score; }

private:
	void checkPaddleCollision();
	void handleCollision(bool isLeftPaddle);

	// Helper references
	Aquarius::Application& app = *Aquarius::Application::get();
	Aquarius::Window& window = *app.getWindow();
	
	// Pong specific stuff
	Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_Camera;
	Aquarius::sharedPtr<Aquarius::Texture> m_BackgroundTexture;
	Paddle m_LeftPaddle;
	Paddle m_RightPaddle;
	Ball m_Ball;
	Score score = { 0, 0 };

	// State management
	bool m_isPaused = false;
};
