include "dependencies.lua"

workspace "Skribble"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	flags
	{
		"MultiProcessorCompile"
	}



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
include "Skribble/vendor/GLFW"
include "Skribble/vendor/GLAD"
include "Skribble/vendor/FreeType"
include "Skribble/vendor/OpenAL-Soft"
include "Skribble/vendor/Vorbis"
include "Skribble/vendor/libogg"
include "Skribble/vendor/libwav"
group ""

include "Skribble"
include "Game"