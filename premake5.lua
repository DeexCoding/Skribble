workspace "Skribble"
	architecture "x64"

	configurations
	{
		"Debug",
		"Relese",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Skribble"
	location "Skribble"
	kind "SharedLib"
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
		"%{prj.name}/vendor/spdlog/include"
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
		symbols "On"

	filter "configurations:Relese"
		defines "SKRIBBLE_RELESE"
		optimize "On"

	filter "configurations:Distribution"
		defines "SKRIBBLE_DISTRIBUTION"
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
		symbols "On"

	filter "configurations:Relese"
		defines "SKRIBBLE_RELESE"
		optimize "On"

	filter "configurations:Distribution"
		defines "SKRIBBLE_DISTRIBUTION"
		optimize "On"