#include "pch.h"

#include "Game.h"
#include "Collision.h"
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

			if (!m_KeyPressed[wParam])	
				m_KeyPressed[wParam] = true;

			return 0;
		}

		case WM_KEYUP:
		{
			if (m_KeyPressed[wParam])
				m_KeyPressed[wParam] = false;

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

// Checks player input
void Game::CheckInput()
{
	if ((m_KeyPressed[VK_SPACE] || m_KeyPressed[SKEL_KEY_W]) && !m_KeySpace)
	{
		m_KeySpace = true;
		m_Skeleton.Jump();
	}

	if (m_KeyPressed[SKEL_KEY_D])
		MoveSkeleton(Direction::Right);
	else if (m_KeyPressed[SKEL_KEY_A])
		MoveSkeleton(Direction::Left);
}

void Game::MoveSkeleton(Direction dir)
{

	if (GetAsyncKeyState(VK_SHIFT))
		m_Skeleton.InSpeedSprint(dir);
	else
		m_Skeleton.InSpeedWalk(dir);
}

// Checks to see if anyting is colliding with an level object
void Game::CheckObjectColison()
{
	const std::deque<DrawObject>& obj = Level::GetObjects();

	for (const auto& o : obj)
	{
		if (!Collision::IsCollideable(o.Type)) continue;

		const HitBox& hit = m_Skeleton.GetHitBox();
		if (Collision::CollisionYUp(o, hit)) {
			m_Skeleton.SetY(o.TopLeft.Y - (hit.BottomRight.Y - hit.TopLeft.Y) - 29);
			SetCanJump();	
			m_Skeleton.SetCanJump();
		} 
		else if (Collision::CollisionYDown(o, hit)) {
			m_Skeleton.SetY(m_Skeleton.GetY() - m_Skeleton.GetYSpeed());
			m_Skeleton.SetYSpeed(0);
		}
		else if (Collision::CollisionXLeft(o, hit)) {
			m_Skeleton.SetX(o.TopLeft.X - (hit.BottomRight.X - hit.TopLeft.X) - (hit.TopLeft.X - m_Skeleton.GetX()));
		} 
		else if (Collision::CollisionXRight(o, hit)) {
			m_Skeleton.SetX(o.BottomRight.X - (hit.BottomRight.X - hit.TopLeft.X) - (hit.TopLeft.X - m_Skeleton.GetX()));
		}

	}
}

// Sets the input so it can jump
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

// I just feel that his should be overloaded
void operator*=(D2D1_SIZE_F& size, float muli)
{
	size.width *= muli;
	size.height *= muli;
}

// Inits the game and gives the hinstance to the window class
int Game::InitInter(HINSTANCE hInst)
{
	int result = Window::Init(hInst);

	if (result)
		return -1;

	Window::MakeWindow();

	Level::Load();

	m_SkelSize = m_Skeleton.GetSize();

	m_SkelSize *= SKEL_DEFUALT_SKELETON_SCALE * 1.5f; // we need this because of the white space in the photos

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

	m_Skeleton.Move();

	CheckInput();
	CheckObjectColison();

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
	// Copy the sprite
	Graphics::SetDrawColor(1.0f, 0.0f, 0.0f);

	Level::Draw();
	
#if _DEBUG || DEBUG
	Graphics::DrawRect(m_Skeleton.GetX(), m_Skeleton.GetY(), 
		m_Skeleton.GetX() + m_SkelSize.width + 10,
		m_Skeleton.GetY() + (int)m_SkelSize.height + 10, 
		false);

	Graphics::SetDrawColor(1.0f, 1.0f, 1.0f);
	Render::DrawHitBox(m_Skeleton.GetHitBox());
#endif

	Render::DrawSkeleton(m_Skeleton);

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
