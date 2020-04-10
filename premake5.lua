workspace "Jank"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Jank/vendor/GLFW/include"

include "Jank/vendor/GLFW"

project "Jank"
	location "Jank"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Jankpch.h"
	pchsource "Jank/src/Jankpch.cpp"

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
			"JANK_PLATFORM_WINDOWS",
			"JANK_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "JANK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JANK_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JANK_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
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
		"Jank/vendor/spdlog/include",
		"Jank/src"
	}

	links
	{
		"Jank"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"JANK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JANK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JANK_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JANK_DIST"
		optimize "On"