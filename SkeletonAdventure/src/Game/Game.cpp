#include "pch.h"

#include "Game.h"
#include "Window/Window.h"


Game::Game()
{
}

#ifdef _DEBUG
std::map<UINT, bool> HaveSeen;
#endif
// Handles the messages we get from the window
LRESULT CALLBACK Game::WindowProcInter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	if (HaveSeen.find(message) == HaveSeen.end())
		HaveSeen.insert(std::pair<UINT, bool>(message, true));
#endif // For message debugging

	switch (message)
	{
		case WM_PAINT:
		{
			Window::Draw();
			return 0;
		}
		case WM_QUIT:
		{
			PostQuitMessage(0);
			DestroyWindow(Window::GetWindow());
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
			DestroyWindow(Window::GetWindow());
			return 0;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);

}

// Inits the game and gives the hinstance to the window class
int Game::InitInter(HINSTANCE hInst)
{
	int result = Window::Init(hInst);

	if (result)
		return -1;


	
	Window::MakeWindow();

	return 0;

}

// Returns if the game should close
bool Game::ShouldCloseInter()
{
	return Window::ShouldClose() || m_ShouldClose;
}

// Runs the game and pulls messages from the window class
void Game::RunInter()
{
	Window::Run();



}

// Singleton Redirect to Game::WindowProcInter
// Handles the messages from windows
LRESULT CALLBACK Game::GameWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParma)
{
	return Get().WindowProcInter(hWnd, message, wParam, lParma);
}

// Singleton Redirect to Game::InitInter
// Inits the game
int Game::Init(HINSTANCE Instance)
{
	return Get().InitInter(Instance);
}

// Singleton Redirect to Game::ShouldCloseInter
// returns if we need to close or not
bool Game::ShouldClose()
{
	return Get().ShouldCloseInter();
}

// Singleton Redirect to Game::RunInter()
// Runs the game logic and pulls messages from the window class
void Game::Run()
{
	Get().RunInter();
}

// Gets the instance of the game object
Game& Game::Get()
{
	static Game game;
	return game;
}
