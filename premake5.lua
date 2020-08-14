workspace "Skribble"
	architecture "x86_x64"

	configurations
	{
		"Debug",
		"Relese",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Skribble/vendor/GLFW/include"

group "Dependecies"
include "Skribble/vendor/GLFW"
group ""

project "Skribble"
	location "Skribble"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "skpch.h"
	pchsource "Skribble/src/skpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SKRIBBLE_WINDOWS",
			"SKRIBBLE_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}

	filter "configurations:Debug"
		defines "SKRIBBLE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Relese"
		defines "SKRIBBLE_RELESE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "SKRIBBLE_DISTRIBUTION"
		buildoptions "/MD"
		optimize "On"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Skribble/vendor/spdlog/include",
		"Skribble/src"
	}

	links
	{
		"Skribble"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SKRIBBLE_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SKRIBBLE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Relese"
		defines "SKRIBBLE_RELESE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "SKRIBBLE_DISTRIBUTION"
		buildoptions "/MD"
		optimize "On"