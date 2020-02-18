#include "pch.h"

#include "Render.h"
#include "Graphics.h"





// Sets the window handle to the render and graphics engine internal
void Render::InitInter(HWND wnd)
{
	Graphics::Init(wnd);
}

// Sets the window handle to the render
void Render::Init(HWND wnd)
{
	Get().InitInter(wnd);
}

// Starts the render Internal
void Render::StartRenderInter()
{
	Graphics::StartDraw();
}

// Starts the render
void Render::StartRender()
{
	Get().StartRenderInter();
}

// Ends the render Internal
void Render::EndRenderInter()
{
	Graphics::EndDraw();
}

// Ends the render
void Render::EndRender()
{
	Get().EndRenderInter();
}


// Gets the only object of the Render class
Render& Render::Get()
{
	static Render render;
	return render;
}

Render::Render()
{

}

