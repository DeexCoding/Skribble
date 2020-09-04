#pragma once

namespace Skribble
{
	class GrphicsContext
	{
	public:
		virtual void Initalize() = 0;
		virtual void SwapBuffers() = 0;

	};
}
