project "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Skribble/vendor/spdlog/include",
		"%{wks.location}/Skribble/src",
		"%{wks.location}/Skribble/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.FreeType}"
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