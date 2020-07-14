#pragma once

#include "Core.h"

namespace Skribble
{
	class SKRIBBLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//Define in CLIENT
	Application* CreateApplication();
}