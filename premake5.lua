workspace "Jank"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["Glad"] = "Jank/vendor/Glad/include"
IncludeDir["ImGui"] = "Jank/vendor/ImGui"
IncludeDir["glm"] = "Jank/vendor/glm"

include "Jank/vendor/GLFW"
include "Jank/vendor/Glad"
include "Jank/vendor/ImGui"

project "Jank"
	location "Jank"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Jankpch.h"
	pchsource "Jank/src/Jankpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"JANK_PLATFORM_WINDOWS",
			"JANK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "JANK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JANK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JANK_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
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
		"Jank/vendor/spdlog/include",
		"Jank/src",
		"Jank/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Jank"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"JANK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JANK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "JANK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "JANK_DIST"
		runtime "Release"
		optimize "on"