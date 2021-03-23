#include "Paddle.h"

#include "Aquarius.h"


void Paddle::Render() const 
{
	Aquarius::Renderer::DrawQuad(
		position,
		size,
		paddleTexture.get()
	);
}
