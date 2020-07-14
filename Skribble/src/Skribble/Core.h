#pragma once

#ifdef SKRIBBLE_WINDOWS
	#ifdef SKRIBBLE_DLL
		#define SKRIBBLE_API __declspec(dllexport)
	#else
		#define SKRIBBLE_API __declspec(dllimport)
	#endif
#else
	#error Skribble only supports Windows!
#endif