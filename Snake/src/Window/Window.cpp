#include "Window.h"
#include "Game/Core.h"

// Inits GLFW
int Window::Init()
{
	if (!glfwInit())
		return -1;

	return 0;
}

// Creates the window
GLFWwindow* Window::CreateWindow()
{
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_Wnd = glfwCreateWindow(SNAKE_WND_WIDHT, SNAKE_WND_HEIGHT, "Snake", NULL, NULL);

	if (!m_Wnd)
	{
		glfwTerminate();
		return nullptr;
	}

	return m_Wnd;
}

// Clears the color buffer and prepares for rendering
void Window::StartRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

// Swaps the buffer and gets events
void Window::EndRender()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(m_Wnd);

	/* Poll for and process events */
	glfwPollEvents();
}

// Clean up : Once the window is gone we no longer need glfw or open gl
Window::~Window()
{
	glfwTerminate();
}