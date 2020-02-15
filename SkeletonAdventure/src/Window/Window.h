#ifndef WINDOW_H
#define WINDOW_H

// Singleton Window Class
class Window
{
private:

	int InitInter();
	bool ShouldCloseInteral();
	void RunInter();

	GLFWwindow* GetWindowInter();

	GLFWwindow* CreateWindowInter();

	GLFWwindow* m_Wnd = nullptr;

	Window();
public:
	Window(const Window&) = delete; // No copying

	static Window& Get();

	static GLFWwindow* GetWindow();
	static int Init();
	static GLFWwindow* CreateWindow();
	static bool ShouldClose();
	static void Run();
};

#endif /* WINDOW_H */
