#include "pch.h"

#include "Window.h"
#include "Game/Game.h"
#include "Render.h"

// Made Private for singleton
Window::Window()
{
}

// Internal

// Inits the window class and registers it
int Window::InitInter(HINSTANCE hInst)
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = Game::GameWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = SKEL_WINDOW_CLASS;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);


	return 0;
}

// Creates the window and sets the classes handle to it also inits the render
void Window::CreateWindowInter()
{
	m_hWnd = CreateWindowEx(
		0,
		SKEL_WINDOW_CLASS,
		L"Skeleton Adventure",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0, 0, SKEL_WINDOW_WIDTH, SKEL_WINDOW_HEIGHT, // X, Y Pos, Width and height
		nullptr,
		nullptr,
		m_hInst,
		nullptr
	);

	Render::Init(m_hWnd);

	ShowWindow(m_hWnd, SW_SHOW);
}

// Returns if the window should close and calls GetMessage for windows API
bool Window::ShouldCloseInteral()
{
	BOOL Result = GetMessage(
		&m_Msg,
		nullptr,
		0,
		0
	);
	return Result < 1;
}

// Handles Messages
void Window::RunInter()
{
	TranslateMessage(&m_Msg);
	DispatchMessage(&m_Msg);
}

// Tells the render what to draw
void Window::DrawInter()
{
	Render::StartRender();



	Render::EndRender();
}

// Gets the current window handle
HWND Window::GetWindowInter()
{
	return m_hWnd;
}

// Public
Window& Window::Get()
{
	static Window wnd; // This throws an exception for some reason
	return wnd;
}

// All of these functions get inlined by the compiler
// Inits GLFW and the window
int Window::Init(HINSTANCE hInstance)
{
	return Get().InitInter(hInstance);
}

// Returns if the window should close
bool Window::ShouldClose()
{
	return Get().ShouldCloseInteral();
}

// Gets and processes the messages from the window
void Window::Run()
{
	Get().RunInter();
}

// Creates the window
void Window::MakeWindow()
{
	return Get().CreateWindowInter();
}

// Draws to the window
void Window::Draw()
{
	Get().DrawInter();
}

// Gets the window handle
HWND Window::GetWindow()
{
	return Get().GetWindowInter();
}