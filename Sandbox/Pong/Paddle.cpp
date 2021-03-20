#include "Paddle.h"


void Paddle::Render() const 
{
	Aquarius::Renderer::DrawQuad(
		position,
		size,
		0,
		{ 1.0, 0.5, 1.0, 1.0 }
	);
}
