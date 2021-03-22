#pragma once

#include "Aquarius.h"


class PongLayer;

struct Ball
{
	void Render() const;
	void Update(Aquarius::timeDelta_t dt);
	void Reset(bool leftScored);
	
	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 speed;
	glm::vec2 velocity;
	PongLayer* game;
};
