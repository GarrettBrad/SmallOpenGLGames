#ifndef RENDER_H
#define RENDER_H

#include "Game/Skeleton.h"

namespace Render
{
	void StartRender();

	void DrawSkeleton(const Skeleton& skeli);
	void DrawGround();

	void EndRender(GLFWwindow* wnd);
}

#endif /* RENDER_H*/
