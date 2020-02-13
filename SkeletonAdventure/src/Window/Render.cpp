#include "pch.h"

#include "Render.h"


namespace Render
{

	void StartRender()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void EndRender(GLFWwindow* wnd)
	{	
		/* Swap front and back buffers */
		glfwSwapBuffers(wnd);

		/* Poll for and process events */
		glfwPollEvents();
	}


}