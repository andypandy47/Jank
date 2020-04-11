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
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

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
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"JANK_PLATFORM_WINDOWS",
			"JANK_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "JANK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "JANK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "JANK_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

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
		"%{IncludeDir.glm}"
	}

	links
	{
		"Jank"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"JANK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JANK_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "JANK_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "JANK_DIST"
		runtime "Release"
		optimize "On"