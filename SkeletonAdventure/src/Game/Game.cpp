#include "pch.h"

#include "Game.h"
#include "Window/Window.h"

void Game::KeyCallBack(GLFWwindow* wnd, int key, int scanecode, int action, int mods)
{ 
	// Hold Keys
	if (action == GLFW_REPEAT)
	{
		switch (key)	
		{
			case GLFW_KEY_D:
			{
				if (glfwGetKey(wnd, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
					Get().m_Skeleton.InSpeedSprint(Direction::Right);
				else 
					Get().m_Skeleton.InSpeedSprint(Direction::Right);

				break;
			}
			case GLFW_KEY_A:
			{
				if (glfwGetKey(wnd, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
					Get().m_Skeleton.InSpeedSprint(Direction::Left);
				else
					Get().m_Skeleton.InSpeedWalk(Direction::Left);

				break;
			}
		}
	}

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_SPACE:
			{
				Get().m_Skeleton.Jump();
			}
		}
	}
}

int Game::InitInter()
{
	int result = Window::Init();

	if (result)
		return -1;


	GLFWwindow* wnd = Window::CreateWindow();

	if (!wnd)
		return -2;

	return 0;

}

bool Game::ShouldCloseInter()
{
	return Window::ShouldClose() || m_ShouldClose;
}

void Game::RunInter()
{

	Window::Run();


}


int Game::Init()
{
	return Get().InitInter();
}

bool Game::ShouldClose()
{
	return Get().ShouldCloseInter();
}

void Game::Run()
{
	Get().RunInter();
}

Game& Game::Get()
{
	static Game game;
	return game;
}
