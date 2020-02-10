#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* m_Wnd = nullptr;
public:
	int Init();

	GLFWwindow* CreateWindow();

	inline GLFWwindow* GetWindow() { return m_Wnd; }

	// Called every frame : Returns if the window should close
	inline int ShouldClose() { return glfwWindowShouldClose(m_Wnd); }

	void StartRender();
	void EndRender();

	// Window(); // Not needed
	~Window();
};

#endif /* WINDOW_H */
