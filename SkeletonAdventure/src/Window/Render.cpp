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

// Handles drawing the skeleton
void Render::DrawEntityInter(const Entity& ent, float& scale)
{
	ent.GetSprite()->Draw((float)ent.GetX(), (float)ent.GetY(), scale);
}
// Draws the Skeleton returns the size of the sprite
void Render::DrawEntity(const Entity& ent, float scale)
{
	Get().DrawEntityInter(ent, scale);
}

// Draws the level
void Render::DrawLevelObjectsInter(const DrawObject& obj)
{
	Graphics::DrawRect(obj.TopLeft.X, obj.TopLeft.Y, obj.BottomRight.X, obj.BottomRight.Y);
}
// Draws the object given to it
void Render::DrawLevelObjects(const DrawObject& obj)
{
	Get().DrawLevelObjectsInter(obj);
}

void Render::DrawHitBoxInter(const HitBox& hit)
{
	Graphics::DrawRect(hit.TopLeft.X,

		hit.TopLeft.Y,

		hit.BottomRight.X,

		hit.BottomRight.Y,
		false);
}
void Render::DrawHitBox(const HitBox& hit)
{
	Get().DrawHitBoxInter(hit);
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


