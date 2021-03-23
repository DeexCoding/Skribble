#pragma once

#include "Core.h"

#ifdef  SKRIBBLE_WINDOWS

extern Skribble::Application* Skribble::CreateApplication();

int main(int argc, char** argv)
{
	Skribble::Debug::Initalize();

	SKRIBBLE_PROFILE_BEGIN_SESSION("Startup", "Skribble_Profile_Startup.json");
	auto app = Skribble::CreateApplication();
	SKRIBBLE_PROFILE_END_SESSION();

	SKRIBBLE_PROFILE_BEGIN_SESSION("Run", "Skribble_Profile_Runtime.json");
	app->Run();
	SKRIBBLE_PROFILE_END_SESSION();

	SKRIBBLE_PROFILE_BEGIN_SESSION("End", "Skribble_Profile_Shutdown.json");
	delete app;
	SKRIBBLE_PROFILE_END_SESSION();
}

#endif