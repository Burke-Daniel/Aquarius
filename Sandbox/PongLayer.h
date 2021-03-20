#pragma once

#include "Aquarius.h"


struct Paddle
{
	void Render();
	void moveUp(Aquarius::timeDelta_t dt);
	void moveDown(Aquarius::timeDelta_t dt);
	glm::vec2 position;
	glm::vec2 size;
	double speedY;
};

class PongLayer : public Aquarius::Layer
{
public:
	PongLayer();

	void onCreation() override;
	void onEvent(const Aquarius::Event&) override;
	void onUpdate(Aquarius::timeDelta_t) override;

private:
	Aquarius::sharedPtr<Aquarius::OrthographicCamera> m_Camera;
	Paddle m_LeftPaddle;
	Paddle m_RightPaddle;
};