#include "pch.h"

#include "Window.h"
#include "Game/Game.h"
#include "Render.h"

// Made Private for singleton
Window::Window()
{
}

// Internal

int Window::InitInter()
{
	if (!glfwInit())
		return -1;

	return 0;
}

GLFWwindow* Window::GetWindowInter()
{
	return m_Wnd;
}

GLFWwindow* Window::CreateWindowInter()
{
	// Only let 1 window be created
	if (m_Wnd) return m_Wnd;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_Wnd = glfwCreateWindow(SKEL_WINDOW_WIDTH, SKEL_WINDOW_HEIGHT, "Snake", NULL, NULL);

	if (!m_Wnd)
	{
		glfwTerminate();
		return nullptr;
	}

	glfwSetKeyCallback(m_Wnd, Game::KeyCallBack);

	return m_Wnd;
}

// Returns if the window should close
bool Window::ShouldCloseInteral()
{
	return glfwWindowShouldClose(m_Wnd);
}

// Render the frame
void Window::RunInter()
{
	Render::StartRender();

	// DrawS

	Render::EndRender(m_Wnd);
}

// Public
Window& Window::Get()
{
	static Window wnd; // This throws an exception for some reason
	return wnd;
}

// All of these functions get inlined by the compiler
// Inits GLFW and the window
int Window::Init()
{
	return Get().InitInter();
}

bool Window::ShouldClose()
{
	return Get().ShouldCloseInteral();
}

void Window::Run()
{
	Get().RunInter();
}

GLFWwindow* Window::GetWindow()
{
	return Get().GetWindowInter();
}

GLFWwindow* Window::CreateWindow()
{
	return Get().CreateWindowInter();
}