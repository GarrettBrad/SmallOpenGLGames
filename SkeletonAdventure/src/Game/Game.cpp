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
			m_KeyPressed[wParam] = true;
			KeyPressed(wParam, lParam);

			return 0;
		}

		case WM_KEYUP:
		{
			m_KeyPressed[wParam] = false;
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

// A key is pressed
// Might get rid of
void Game::KeyPressed(WPARAM wParam, LPARAM lParam)
{
	// Switch statements break the input part because of how window messages work so we are going to have
	
}

// A key is Released
// Might get rid of 
void Game::KeyReleased(WPARAM wParam, LPARAM lParam)
{

	//switch (wParam)
	//{
	//	case VK_SPACE:
	//	{
	//		if (m_Skeleton.GetCanJump())
	//			m_KeySpace = false;
	//		return;
	//	}
	//}
}

void Game::CheckInput()
{
	if (m_KeyPressed[VK_SPACE] && !m_KeySpace)
	{
		m_KeySpace = true;
		m_Skeleton.Jump();
	}

	if (m_KeyPressed[VK_RIGHT])
		MoveSkeleton(Direction::Right);
	else if (m_KeyPressed[VK_LEFT]) 
		MoveSkeleton(Direction::Left);
}

void Game::MoveSkeleton(Direction dir)
{

	if (GetAsyncKeyState(VK_SHIFT))
		m_Skeleton.InSpeedSprint(dir);
	else
		m_Skeleton.InSpeedWalk(dir);
}

// Checks the that the player hasn't gone off screen
void Game::CheckBoarders()
{
	// To far left
	if (m_Skeleton.GetX() < 0)
		m_Skeleton.SetX(0);

	if (m_Skeleton.GetY() < 0)
		m_Skeleton.SetY(0);

	if ((m_Skeleton.GetX() + m_CurrentSkelSize.width) > SKEL_WINDOW_WIDTH)
		m_Skeleton.SetX(SKEL_WINDOW_WIDTH - m_CurrentSkelSize.width);

	if ((m_Skeleton.GetY() + m_CurrentSkelSize.height + SKEL_Y_CORD_CUSHIN) > SKEL_WINDOW_HEIGHT)
	{
		m_Skeleton.SetY(SKEL_WINDOW_HEIGHT - m_CurrentSkelSize.height - SKEL_Y_CORD_CUSHIN);
	
		SetCanJump();
		m_Skeleton.SetCanJump();
	}
}

void Game::SetCanJumpInter()
{
	m_KeySpace = false;
}
void Game::SetCanJump()
{
	Get().SetCanJumpInter();
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
	auto again = std::chrono::high_resolution_clock::now();

	using namespace std::chrono_literals;

	again += std::chrono::milliseconds(25);

	m_Skeleton.Move();

	CheckInput();
	CheckBoarders();

	Window::Run();

	// Only run 1 frame every 25 milliseconds
	if (again > std::chrono::high_resolution_clock::now())
		std::this_thread::sleep_until(again);
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
	// Copy the sprite
	m_CurrentSkelSize = Render::DrawSkeleton(m_Skeleton);

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
