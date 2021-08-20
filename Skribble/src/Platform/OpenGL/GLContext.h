#pragma once

#include "Skribble/Render/GraphicsContext.h"

#ifdef SKRIBBLE_DEBUG
#if 1
#define DEBUG_GL
#endif
#endif

struct GLFWwindow;

namespace Skribble
{
	class GLContext : public GrphicsContext
	{
	public:
		GLContext(GLFWwindow* _window);

		virtual void Initalize() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* window;
	};
}