#include "skpch.h"
#include "GLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Skribble
{
#ifdef DEBUG_GL
	void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		SKRIBBLE_CORE_ERROR("OpenGL error : {0}", message);
		SKRIBBLE_CORE_ASSERT(false, "OpenGL error!");
	}

#endif

	GLContext::GLContext(GLFWwindow* _window) : window(_window)
	{

	}

	void GLContext::Initalize()
	{
		SKRIBBLE_PROFILE_SCOPE("GLContext::Initalize");

		glfwMakeContextCurrent(window);
		int glad = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SKRIBBLE_CORE_ASSERT(glad, "Couldn't initalize Glad!");
#ifdef DEBUG_GL
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
#endif
	}

	void GLContext::SwapBuffers()
	{
		SKRIBBLE_PROFILE_SCOPE("GLContext::SwapBuffers");

		glfwSwapBuffers(window);
	}
}