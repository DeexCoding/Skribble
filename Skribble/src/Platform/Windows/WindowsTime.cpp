#include "skpch.h"

#include "Skribble/Core/Time.h"

#include <GLFW/glfw3.h>

#if SKRIBBLE_WINDOWS

namespace Skribble
{
	float Time::GetCurrentRealTime()
	{
		return (float)glfwGetTime();
	}
}

#endif