#include "pch.h"

#include "Game.h"
#include "Window/Window.h"

int Game::Init()
{
	int result = Window::Init();

	if (result)
		return -1;


	GLFWwindow* wnd = Window::CreateWindow();

	if (!wnd)
		return -2;

	return 0;

}

bool Game::ShouldClose()
{
	return Window::ShouldClose() || m_ShouldClose;
}

void Game::Run()
{
	Window::Run();
}
