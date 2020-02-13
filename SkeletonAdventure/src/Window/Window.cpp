#include "pch.h"

#include "Window.h"
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

GLFWwindow* Window::CreateWindowInter()
{
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_Wnd = glfwCreateWindow(SKEL_WINDOW_WIDTH, SKEL_WINDOW_HEIGHT, "Snake", NULL, NULL);

	if (!m_Wnd)
	{
		glfwTerminate();
		return nullptr;
	}

	return m_Wnd;
}

bool Window::ShouldCloseInteral()
{
	return glfwWindowShouldClose(m_Wnd);
}

void Window::RunInter()
{
	Render::StartRender();

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

GLFWwindow* Window::CreateWindow()
{
	return Get().CreateWindowInter();
}