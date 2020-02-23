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
	// this stops recreating the sprite if the image is the same
	if (m_LastInfo.file != skel.GetImage().file)
	{
		m_LastInfo = skel.GetImage();
		
		// Deletes SkeletonSprite if there is a new one in que
		if (m_SkeletonSprite)
		{
			delete m_SkeletonSprite;
			m_SkeletonSprite = nullptr;
		}
	}

	// Creates a new sprite to be drawing
	if (!m_SkeletonSprite)
	{
		m_SkeletonSprite = new Sprite(skel.GetImage());
	}

	m_SkeletonSprite->Draw(skel.GetX(), skel.GetY(), scale);

	return m_SkeletonSprite->GetSize();

}
// Draws the Skeleton returns the size of the sprite
D2D1_SIZE_F Render::DrawSkeleton(const Skeleton& skel, float scale)
{
	return Get().DrawSkeletonInter(skel, scale);
}

// Draws the level
void Render::DrawLevelObjectsInter(const DrawObject& obj)
{
	Graphics::DrawRect(obj.TopLeft.X, obj.TopLeft.Y, obj.BottomRight.X, obj.BottomRight.Y);
}
// Draws the ojbect given to it
void Render::DrawLevelObjects(const DrawObject& obj)
{
	Get().DrawLevelObjectsInter(obj);
}

void Render::DrawHitBoxInter(const HitBox& hit)
{
	// for somereason when drawn the hitbox is offset
	Graphics::DrawRect(hit.TopLeft.X,
		hit.TopLeft.Y - 13,
		hit.BottomRight.X,
		hit.BottomRight.Y - 13,
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

Render::~Render()
{
	// Makes sure m_SkeletonSprite was cleaned up
	if (m_SkeletonSprite)
		delete m_SkeletonSprite;
}

