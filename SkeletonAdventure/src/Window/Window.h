#ifndef WINDOW_H
#define WINDOW_H

// Singleton Window Class
class Window
{
private:

	HINSTANCE m_hInst = nullptr;
	HWND m_hWnd = nullptr;
	MSG m_Msg;

	HWND GetWindowInter();

	int InitInter(HINSTANCE hInst);
	int ExitCodeInter();
	bool ShouldCloseInteral();
	void CreateWindowInter();
	void RunInter();
	void DrawInter();

	
	Window();
public:
	Window(const Window&) = delete; // No copying

	static Window& Get();

	static HWND GetWindow();
	static int Init(HINSTANCE hInst);
	static int ExitCode();
	static void MakeWindow();
	static bool ShouldClose();
	static void Run();
	static void Draw();
};

#endif /* WINDOW_H */
