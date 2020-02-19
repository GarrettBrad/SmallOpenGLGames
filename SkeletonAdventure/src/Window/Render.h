#ifndef RENDER_H
#define RENDER_H

#include "Game/Skeleton.h"
#include "Sprite.h"

// Game tell Render what to render
// Render Tells Graphics how to render
// Graphics makes the graphics
//
// This is for larger objects such as a skeleton or other.
// for lines and other stuff Graphics can be called directly
class Render
{
private:

	// Temp for testing
	Render();
	~Render();

	void InitInter(HWND wnd);

	void StartRenderInter();

	D2D1_SIZE_F DrawSkeletonInter(const Skeleton& skel, float& scale);

	void EndRenderInter();

public:

	static void Init(HWND wnd);

	static void StartRender();

	static D2D1_SIZE_F DrawSkeleton(const Skeleton& skel, float scale = SKEL_DEFUALT_SKELETON_SCALE);


	static void EndRender();

	static Render& Get();

};

#endif /* RENDER_H*/
