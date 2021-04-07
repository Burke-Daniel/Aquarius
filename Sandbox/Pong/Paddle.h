#pragma once

#include "Aquarius.h"

class PaddleController;


struct Paddle
{
	void Render() const;
	void ChangePaddleController(Aquarius::uniquePtr<PaddleController> paddleController);
	Aquarius::sharedPtr<Aquarius::Texture> paddleTexture;
	Aquarius::uniquePtr<PaddleController> controller;
	glm::vec2 position;
	glm::vec2 size;
	float speedY;
};
