#pragma once

#include "Core.h"

#ifdef  SKRIBBLE_WINDOWS

extern Skribble::Application* Skribble::CreateApplication();

int main(int argc, char** argv)
{
	Skribble::Debug::Initalize();

	SKRIBBLE_CORE_TRACE("Hello");

	auto app = Skribble::CreateApplication();
	app->Run();
	delete app;
}

#endif