#include "skpch.h"
#include "GLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Skribble
{
	GLContext::GLContext(GLFWwindow* _window) : window(_window)
	{

	}

	void GLContext::Initalize()
	{
		SKRIBBLE_PROFILE_SCOPE("GLContext::Initalize");

		glfwMakeContextCurrent(window);
		int glad = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SKRIBBLE_CORE_ASSERT(glad, "Couldn't initalize Glad!");
	}

	void GLContext::SwapBuffers()
	{
		SKRIBBLE_PROFILE_SCOPE("GLContext::SwapBuffers");

		glfwSwapBuffers(window);
	}
}