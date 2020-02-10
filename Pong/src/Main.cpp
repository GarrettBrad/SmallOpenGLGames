
// I didn't feel a precompiled header was need for a project this small

// Built with Visual Studio 2019

#include "Game/Game.h"

int main()
{
	Game game;

	game.PlayerSelect();

	// I create this on the heap so there isn't a int just floating around doing nothing until the programe ends
	int* gameInitError = new int;

	*gameInitError = game.Init();

	if (*gameInitError)
		return *gameInitError;

	delete gameInitError;

	while (!game.ShouldClose())
	{
		game.Run();
	}

	return 0;
}