#include <cmath>

#include "Render.h"
#include "GLFW/glfw3.h"

#define PONG_PI 3.14159265359

// Renders the given Paddle
void Render::RenderPaddle(const Paddle& player)
{
	glBegin(GL_POLYGON);
		glVertex2f(player.GetX() + player.c_Width, player.GetY() + player.c_Height);
		glVertex2f(player.GetX() - player.c_Width, player.GetY() + player.c_Height);
		glVertex2f(player.GetX() - player.c_Width, player.GetY() - player.c_Height);
		glVertex2f(player.GetX() + player.c_Width, player.GetY() - player.c_Height);
	glEnd();
}

// Simply just converts radians to degrees
inline float InRadians(const int& degree)
{
	return (float) (180 / PONG_PI) * degree;
}

void Render::RenderBall(const Ball& ball)
{

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(ball.GetX(), ball.GetY());

	for (int i = 0; i < 360; i++)
	{
		// The ball is streached because how OpenGL like its graphics formated. fixed my window Width/ Height
		float x = ball.GetX() + (ball.c_Radius * cosf(InRadians(i)) * (720.0f / 1080.0f));
		float y = ball.GetY() + (ball.c_Radius * sinf(InRadians(i)));

		glVertex2f(x, y);
	}

	glEnd();
}