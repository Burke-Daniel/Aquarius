#pragma once

#include "Aquarius.h"

class PaddleController;


struct Paddle
{
	void Render() const;
	Aquarius::uniquePtr<PaddleController> controller;
	glm::vec2 position;
	glm::vec2 size;
	double speedY;
};
