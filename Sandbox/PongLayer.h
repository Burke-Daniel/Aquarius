#pragma once

#include "Aquarius.h"

#include "Pong/Ball.h"
#include "Pong/Paddle.h"
#include "Pong/PaddleController.h"

#include <future>


struct Score
{
	uint8_t RightScore;
	uint8_t LeftScore;
};

class PongLayer : public Aquarius::Layer
{
public:
	PongLayer();
	virtual ~PongLayer();

	void onCreation() override;
	void onEvent(const Aquarius::Event&) override;
	void onUpdate(Aquarius::timeDelta_t) override;
	void onDestruction() override;

	void leftScore() { m_Score.LeftScore++; }
	void rightScore() { m_Score.RightScore++; }
	Score getScore() const { return m_Score; }

private:
	void checkPaddleCollision();
	void handleCollision(bool isLeftPaddle);

	// Helper references
	Aquarius::Application& app = *Aquarius::Application::get();
	Aquarius::Window& window = *app.getWindow();
	
	// Pong specific stuff
	Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_Camera;
	Aquarius::sharedPtr<Aquarius::Texture> m_BackgroundTexture;
	Aquarius::sharedPtr<Aquarius::Texture> m_FontTexture;
	Aquarius::sharedPtr<Aquarius::Bitmap> m_Font;
	uint32_t m_PaddleSound;

	Paddle m_LeftPaddle;
	Paddle m_RightPaddle;
	Ball m_Ball;
	Score m_Score = { 0, 0 };

	// State management
	bool m_isPaused = false;

	// Audio
	Aquarius::Sound::Source m_SoundSource;
	std::thread m_SoundThread;
	bool m_SoundThreadShouldExit = false;
};
