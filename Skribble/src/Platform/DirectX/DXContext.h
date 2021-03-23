#pragma once

#include "Skribble/Render/GraphicsContext.h"

#include <Windows.h>

namespace Skribble
{
	class DXContext : public GrphicsContext
	{
	public:
		DXContext(HWND* window);

		virtual void Initalize() override;
		virtual void SwapBuffers() override;

	private:
		HWND* window;
	};
}