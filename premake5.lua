workspace "Skribble"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Skribble/vendor/GLFW/include"
IncludeDir["GLAD"] = "Skribble/vendor/GLAD/include"
IncludeDir["glm"] = "Skribble/vendor/glm"
IncludeDir["stb_image"] = "Skribble/vendor/stb_image"
IncludeDir["FreeType"] = "Skribble/vendor/FreeType/include"

group "Dependecies"
include "Skribble/vendor/GLFW"
include "Skribble/vendor/GLAD"
include "Skribble/vendor/FreeType"
group ""

project "Skribble"
	location "Skribble"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "skpch.h"
	pchsource "Skribble/src/skpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/FreeType/**.h",
		"%{prj.name}/vendor/FreeType/**.c"

	}

	defines
	{
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.FreeType}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "SKRIBBLE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SKRIBBLE_RELESE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "SKRIBBLE_DISTRIBUTION"
		runtime "Release"
		optimize "on"

project "Game"
	location "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Skribble/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Skribble"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "SKRIBBLE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SKRIBBLE_RELESE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "SKRIBBLE_DISTRIBUTION"
		runtime "Release"
		optimize "on"