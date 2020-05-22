workspace "Mayhem"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buidlcfg}-%{cfg.system}-%{cfg.architecture}"

project "Mayhem"
	location "Mayhem"
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
			"MH_PLATFORM_WINDOWS",
			"MH_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MH_DIST"
		symbols "On"


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
		"Mayhem/vendor/spdlog/include",
		"Mayhem/src"
	}

	links
	{
		"Mayhem"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MH_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MH_DIST"
		symbols "On"