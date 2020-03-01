#include "pch.h"

#include "Game/Game.h"

// Visual studio complaining about the WinMain function
#pragma warning(disable : 28251)


/*

Current TODO:
Added constant 30 FPS
Fully Implement Knight and other entities
Add Level loading System
Improve Rendering and Graphics performance
Image flipping doesn't work with Direct 2D (I probably did something wrong

Current Bug:
Jumping is buggy next to a object // I made it less buggy C:
A Key Repeat command causes the game to run faster for some reason // 30fps should fix this

*/

int CALLBACK WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, // Windows please update to get rid of this. Always null
	LPSTR CmdLine, 
	int nCmdShow)
{
	// Created in its own scope so there isn't a int floating around the entire runtime	
	{
		int result = Game::Init(hInstance);

		if (result)
			return result;
	}

	while (!Game::ShouldClose())
	{
		Game::Run();
	}

	return Game::GetExitCode();
}