#include <GLFW/glfw3.h>
#include "Game/Game.h"
#include <iostream>

#pragma warning(push)
#pragma warning(disable : 4068) // MSVC complaining about opengl
#pragma warning(pop)

/*
Currently only have 32 bit binary for GLFW so this is only 32 bit software
*/

int main()
{
	Game game;

	int* result = new int;

	*result = game.Init();

	if (*result) return *result;

	delete result;

	while (!game.ShouldClose())
	{
		game.Run();
	}

	return 0;
}