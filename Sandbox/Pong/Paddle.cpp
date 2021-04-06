#include "Paddle.h"

#include "Aquarius.h"

#include "PaddleController.h"


void Paddle::Render() const 
{
	Aquarius::Renderer::DrawQuad(
		position,
		size,
		paddleTexture.get()
	);
}

void Paddle::ChangePaddleController(Aquarius::uniquePtr<PaddleController> paddleController)
{
	controller = std::move(paddleController);
}
