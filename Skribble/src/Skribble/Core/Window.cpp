#include "skpch.h"

#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/OpenGL/GLWindow.h"

namespace Skribble
{
	Scope<Window> Window::Create(const WindowPropeties& _propeties)
	{

#ifdef SKRIBBLE_WINDOWS

		//return CreateScope<WindowsWindow>(_propeties);
		return CreateScope<GLWindow>(_propeties);

#else

		SKRIBBLE_CORE_ASSERT(false, "(Code shouldn't ever execute here)");
		return nullptr;

#endif

	}
}