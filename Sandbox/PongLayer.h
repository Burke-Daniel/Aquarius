#pragma once

#include "Aquarius.h"


struct Paddle
{
	void Render() const;
	void moveUp(Aquarius::timeDelta_t dt);
	void moveDown(Aquarius::timeDelta_t dt);
	glm::vec2 position;
	glm::vec2 size;
	double speedY;
};

struct Score
{
	uint8_t RightScore;
	uint8_t LeftScore;
};

struct Ball
{
	void Render() const;
	void Update(Aquarius::timeDelta_t dt);
	void Reset(bool leftScored);
	
	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 speed;
	glm::vec2 velocity;
};

class PongLayer : public Aquarius::Layer
{
public:
	PongLayer();

	void onCreation() override;
	void onEvent(const Aquarius::Event&) override;
	void onUpdate(Aquarius::timeDelta_t) override;

private:
	void checkPaddleCollision();
	void handleCollision(bool isLeftPaddle);

	// Helper references
	Aquarius::Application& app = *Aquarius::Application::get();
	Aquarius::Window& window = *app.getWindow();
	 
	Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_Camera;
	Paddle m_LeftPaddle;
	Paddle m_RightPaddle;
	Ball m_Ball;
	Score score = { 0, 0 };
};