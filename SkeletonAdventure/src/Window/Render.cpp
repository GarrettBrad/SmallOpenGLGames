#include "pch.h"

#include "Render.h"


namespace Render
{
	
	// Clears the OpenGl color buffer
	void StartRender()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	// Draws the skeleton
	void DrawSkeleton(const Skeleton& skeli)
	{

	}

	// Draws the ground
	void DrawGround()
	{
		
	}

	// Swaps buffers and takes events
	void EndRender(GLFWwindow* wnd)
	{	
		/* Swap front and back buffers */
		glfwSwapBuffers(wnd);

		/* Poll for and process events */
		glfwPollEvents();
	}


}