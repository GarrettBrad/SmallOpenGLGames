#ifndef RENDER_H
#define RENDER_H

#include "Game/Paddle.h"
#include "Game/Ball.h"


class Render
{
public:
	void RenderPaddle(const Paddle& player);
	void RenderBall(const Ball& ball);
};

#endif /* REDNER_H */
