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

// Handels drawing the skeleton
D2D1_SIZE_F Render::DrawSkeletonInter(const Skeleton& skel, float& scale)
{
	auto spr = Sprite(L"resources/Skeleton/ready_1.png");

	spr.Draw(skel.GetX(), skel.GetY(), scale);

	return spr.GetSize();
}
// Draws the Skeleton returns the size of the sprite
D2D1_SIZE_F Render::DrawSkeleton(const Skeleton& skel, float scale)
{
	return Get().DrawSkeletonInter(skel, scale);
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

// Made for singleton
Render::Render()
{
}

Render::~Render()
{
}

