workspace "Mayhem"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buidlcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Mayhem/vendor/GLFW/include"
IncludeDir["Glad"] = "Mayhem/vendor/Glad/include"
IncludeDir["ImGui"] = "Mayhem/vendor/imgui"

group "Dependencies"
	include "Mayhem/vendor/GLFW"
	include "Mayhem/vendor/Glad"
	include "Mayhem/vendor/imgui"

group ""

project "Mayhem"
	location "Mayhem"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mpch.h"
	pchsource "Mayhem/src/mpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src", 
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
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
			"MH_PLATFORM_WINDOWS",
			"MH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "MH_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MH_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MH_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Mayhem/vendor/spdlog/include",
		"Mayhem/src"
	}

	links
	{
		"Mayhem"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MH_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MH_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MH_DIST"
		runtime "Release"
		optimize "On"