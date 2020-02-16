#ifndef RENDER_H
#define RENDER_H

#include "Game/Skeleton.h"

namespace Render
{
	void Init(HWND wnd);

	void StartRender();

	void DrawSkeleton(const Skeleton& skeli);
	void DrawGround();

	void EndRender();
}

#endif /* RENDER_H*/
