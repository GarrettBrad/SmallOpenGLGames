#include "pch.h"

#include "Game.h"
#include "Window/Window.h"
#include "Window/Render.h"



// Made private for singleton
Game::Game()
{

}

// Handles the messages we get from the window
LRESULT CALLBACK Game::WindowProcInter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
		case WM_LBUTTONDOWN:
		{

			return 0;
		}
		case WM_LBUTTONUP:
		{

			return 0;
		}
		case WM_MOUSEMOVE:
		{
			return 0;
		}
		case WM_KEYDOWN:
		{
			Logic::KeyPressed(wParam);

			return 0;
		}

		case WM_KEYUP:
		{
			Logic::KeyReleased(wParam);

			return 0;
		}

		// Paint message
		case WM_PAINT:
		{
			// Windows already sets drawing to be on a different thread
			Window::Draw();
			return 0;
		}
		case WM_SIZE:
		{
			Graphics::Resize();
			return 0;
		}

		// Closing stuff
		case WM_QUIT:
		{
			PostQuitMessage(0);
			DestroyWindow(Window::GetWindowHandle());
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;	
		}
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			DestroyWindow(Window::GetWindowHandle());
			return 0;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);

}

// Singleton Redirect to Game::WindowProcInter
// Handles the messages from windows
LRESULT CALLBACK Game::GameWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParma)
{
	return Get().WindowProcInter(hWnd, message, wParam, lParma);
}

// Returns if the game should close
bool Game::ShouldCloseInter()
{
	return Window::ShouldClose() || m_ShouldClose;
}

// Singleton Redirect to Game::ShouldCloseInter
// returns if we need to close or not
bool Game::ShouldClose()
{
	return Get().ShouldCloseInter();
}

// Inits the game and gives the hinstance to the window class
int Game::InitInter(HINSTANCE hInst)
{
	int result = Window::Init(hInst);

	if (result)
		return -1;

	Window::MakeWindow();

	Level::Load();

	return 0;

}

// Singleton Redirect to Game::InitInter
// Inits the game
int Game::Init(HINSTANCE Instance)
{
	return Get().InitInter(Instance);
}

// Runs the game and pulls messages from the window class
void Game::RunInter()
{

	// Do all movement
	Logic::Run();


	Window::Run();
}

// Singleton Redirect to Game::RunInter()
// Runs the game logic and pulls messages from the window class
void Game::Run()
{
	Get().RunInter();
}

// called when the game should be drawn
// Tells the render what to draw
void Game::DrawInter()
{
	// Temp
	Graphics::SetDrawColor(1.0f, 0.0f, 0.0f);

	// Draws the level
	Level::Draw();
	
#if _DEBUG || DEBUG

	// White box around the hitbox
	Graphics::SetDrawColor(1.0f, 1.0f, 1.0f);

	Render::DrawHitBox(Logic::cGetSkeleton().GetHitBox());
	Render::DrawHitBox(Logic::cGetSkeleton().Attack());
#endif

	Render::DrawEntity(Logic::GetSkeleton());

}

// Called when the game should be drawn
void Game::Draw()
{
	Get().DrawInter();
}

// Gets the exit code from the window
int Game::GetExitCodeInter()
{
	return Window::ExitCode();
}

// Singleton Redirect to Game::RunInter()
// Gets the exit code for our application
int Game::GetExitCode()
{
	return Get().GetExitCodeInter();
}

// Gets the instance of the game object
Game& Game::Get()
{
	static Game game;
	return game;
}
