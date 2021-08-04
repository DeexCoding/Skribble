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
group ""

include "Skribble"
include "Game"