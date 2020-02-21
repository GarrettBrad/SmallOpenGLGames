#include "pch.h"

#include "Game/Game.h"

int CALLBACK WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, // Windows please update to get rid of this. Always null
	LPSTR CmdLine, 
	int nCmdShow)
{
	Game game;

	// I create this on the heap so we don't have a int doing nothing the entire run time
	int* result = new int;
	*result = game.Init(hInstance);

	if (*result)
		return *result;

	delete result;

	while (!game.ShouldClose())
	{
		game.Run();
	}

	return game.GetExitCode();
}