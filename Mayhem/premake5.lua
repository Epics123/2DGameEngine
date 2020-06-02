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
IncludeDir["glm"] = "Mayhem/vendor/glm"

group "Dependencies"
	include "Mayhem/vendor/GLFW"
	include "Mayhem/vendor/Glad"
	include "Mayhem/vendor/imgui"

group ""

project "Mayhem"
	location "Mayhem"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mpch.h"
	pchsource "Mayhem/src/mpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
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
			"MH_PLATFORM_WINDOWS",
			"MH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "MH_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MH_DIST"
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
		"Mayhem/vendor/spdlog/include",
		"Mayhem/src",
		"Mayhem/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Mayhem"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MH_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "MH_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "MH_DIST"
		runtime "Release"
		optimize "on"
