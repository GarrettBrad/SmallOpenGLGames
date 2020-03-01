#include <GLFW/glfw3.h>
#include "Game/Core.h"
#include "Render.h"

// returns if the Snake pos is == the the tail pos
bool operator==(const Snake& snake, const Snake& snake2)
{
	return ((snake2.X == snake.X) && (snake2.Y == snake.Y));
}

// returns if the Snake pos is == the the tail pos
bool operator==(const Snake& snake, const Fruit& fruit)
{
	return ((snake.X == fruit.X) && (snake.Y == fruit.Y));
}

namespace Render {
	// Translates the Pixel value to a float value glVertex2f can use
	float PixelToFloatY(int pixel)
	{
		return (pixel / (SNAKE_WND_HEIGHT / 2.0f)) - 1.f;
	}

	// Translates the Pixel value to a float value glVertex2f can use
	float PixelToFloatX(int pixel)
	{
		return (pixel / (SNAKE_WND_WIDHT / 2.0f)) - 1.f;
	}

	// Draw the snake vector given
	void DrawSnake(const std::deque<Snake>& snake)
	{
#ifdef _DEBUG // here to make sure the render is working
		glBegin(GL_TRIANGLES);

		glVertex2f(0.9f, 0.9f);
		glVertex2f(0.95f, 0.9f);
		glVertex2f(0.925f, 0.85f);

		glEnd();
#endif

		// Draws all of the snake peices
		for (const auto& s : snake)
		{
			glBegin(GL_POLYGON);
				glVertex2f(PixelToFloatX(s.X + c_SnakeSize), PixelToFloatY(s.Y + c_SnakeSize));
				glVertex2f(PixelToFloatX(s.X - c_SnakeSize), PixelToFloatY(s.Y + c_SnakeSize));
				glVertex2f(PixelToFloatX(s.X - c_SnakeSize), PixelToFloatY(s.Y - c_SnakeSize));
				glVertex2f(PixelToFloatX(s.X + c_SnakeSize), PixelToFloatY(s.Y - c_SnakeSize));
			glEnd();
		}
	}

	void DrawFruit(const Fruit& fruit)
	{
		glBegin(GL_POLYGON);
			glVertex2f(PixelToFloatX(fruit.X + c_SnakeSize), PixelToFloatY(fruit.Y + c_SnakeSize));
			glVertex2f(PixelToFloatX(fruit.X - c_SnakeSize), PixelToFloatY(fruit.Y + c_SnakeSize));
			glVertex2f(PixelToFloatX(fruit.X - c_SnakeSize), PixelToFloatY(fruit.Y - c_SnakeSize));
			glVertex2f(PixelToFloatX(fruit.X + c_SnakeSize), PixelToFloatY(fruit.Y - c_SnakeSize));
		glEnd();
	}

}