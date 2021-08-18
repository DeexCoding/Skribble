project "Skribble"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "skpch.h"
	pchsource "src/skpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"AL_LIBTYPE_STATIC"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.OpenALSoft}",
		"vendor/OpenAL-Soft/src/common",
		"%{IncludeDir.libogg}",
		"%{IncludeDir.Vorbis}",
		"%{IncludeDir.minimp3}",
		"%{IncludeDir.libwav}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"FreeType",
		"OpenAL-Soft",
		"Vorbis",
		"libwav",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "on"
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