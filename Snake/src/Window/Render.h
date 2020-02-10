#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include "Game/Core.h"

enum class Direction
{
	Up,
	Down,
	Right,
	Left
};

struct Snake
{
	int X, Y;
	Direction dir;
	bool FirstObject;
};

struct Fruit
{
	int X, Y;
};

// Returns if the x and y are equal
bool operator==(const Snake& snake, const Snake& snake2);
bool operator==(const Snake& snake, const Fruit& snake2);

namespace Render
{

	const int c_SnakeSize = SNAKE_SIZE; // The distance from the center of the of the snake part

	// Converts a pixel in the x Cord to a OpenGL Cord
	float PixelToFloatX(int pixel);
	// Converts a pixel in the y Cord to a openGl Cord
	float PixelToFloatY(int pixel);

	// Draws a snake to screen
	void DrawSnake(const std::vector<Snake>& snake);
	void DrawFruit(const Fruit& fruit);

}

#endif /* RENDER_H */
