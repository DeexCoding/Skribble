#pragma once

#include "Skribble/Render/GraphicsContext.h"

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