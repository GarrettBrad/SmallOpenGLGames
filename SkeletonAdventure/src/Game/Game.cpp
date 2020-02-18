#include "pch.h"

#include "Game.h"
#include "Window/Window.h"
#include "Window/Render.h"
#include "Window/Graphics.h"



// Made private for singleton
Game::Game()
{
}

// For debugging the messages
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
		case WM_LBUTTONDOWN:
		{
			m_MouseDown = true;
			return 0;
		}
		case WM_LBUTTONUP:
		{
			m_MouseDown = false;
			return 0;
		}
		case WM_MOUSEMOVE:
		{
			m_MouseX = GET_X_LPARAM(lParam);
			m_MouseY = GET_Y_LPARAM(lParam);
			return 0;
		}
		case WM_KEYDOWN:
		{
			KeyPressed(wParam, lParam);
			return 0;
		}

		case WM_KEYUP:
		{
			KeyReleased(wParam, lParam);
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

// Singleton Redirect to Game::WindowProcInter
// Handles the messages from windows
LRESULT CALLBACK Game::GameWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParma)
{
	return Get().WindowProcInter(hWnd, message, wParam, lParma);
}

void Game::KeyPressed(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case SKEL_KEY_A: // A Key
		{
			// Temp
			SetWindowText(Window::GetWindow(), L"A");
		}
	}
}

void Game::KeyReleased(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case SKEL_KEY_A:
		{
			// Temp
			SetWindowText(Window::GetWindow(), L"B");
		}
		// ESCAPE will minimize the application and shift+escape will close it
		case VK_ESCAPE:
		{
			
			if (GetAsyncKeyState(VK_LSHIFT))	{
				DestroyWindow(Window::GetWindow());
				PostQuitMessage(0);
			}

			CloseWindow(Window::GetWindow());
		}
	}
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
	// i.e.
	/* 
	Render::DrawSkeleton();
	
	for (const auto& e : m_Eni) {
		Render::DrawEnemy(e);
	}
	*/

	Graphics::SetDrawColor(1.0f, 0.f, 0.f);

	Graphics::DrawLine(Point(10,10), Point(100,100));
	
	// Draws a line to the mouse when it is clicked
	if (m_MouseDown)
	{
		Graphics::SetDrawColor(1.0f, 0.0f, 1.0f);
		Graphics::DrawLine(Point(10, 10), Point(m_MouseX, m_MouseY));
	}

	Graphics::DrawGrid(20);
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
