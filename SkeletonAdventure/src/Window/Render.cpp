#include "pch.h"

#include "Render.h"


namespace Render
{
	HWND hWnd;
	
	PAINTSTRUCT ps;
	HDC hdc;

	// Sets the window handle to the render
	void Init(HWND wnd)
	{
		hWnd = wnd;
	}


	// Draws the skeleton
	void DrawSkeleton(const Skeleton& skeli)
	{

	}

	// Draws the ground
	void DrawGround()
	{
		
	}

	// Starts the Windows API Render
	void StartRender()
	{
		hdc = BeginPaint(hWnd, &ps);
			
		// Just draws a blue screen TEMP:

		RGB(0, 0, 255);
		FillRect(hdc, &ps.rcPaint, (HBRUSH) COLOR_HIGHLIGHTTEXT);
	}

	// Ends the rendering
	void EndRender()
	{	

		EndPaint(hWnd, &ps);
	}


}