#include "pch.h"

#include "Game/Game.h"

// Visual studio complaining about the WinMain function
#pragma warning(disable : 28251)

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