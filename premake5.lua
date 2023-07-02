workspace "ChickenBroth"
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

IncludeDir["src"] = "ChickenBroth/src"
IncludeDir["vendor"] = "ChickenBroth/vendor"
IncludeDir["spdlog"] = "ChickenBroth/vendor/spdlog/include"
IncludeDir["GLFW"] = "ChickenBroth/vendor/GLFW/include"
IncludeDir["GLAD"] = "ChickenBroth/vendor/GLAD/include"
IncludeDir["imgui"] = "ChickenBroth/vendor/imgui"
IncludeDir["glm"] = "ChickenBroth/vendor/glm"

include "ChickenBroth/vendor/GLFW"
include "ChickenBroth/vendor/GLAD"
include "ChickenBroth/vendor/imgui"

project "ChickenBroth"
    location "ChickenBroth"
    kind "SharedLib"
    language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cbpch.h"
	pchsource "%{prj.name}/src/cbpch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{IncludeDir.src}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CB_PLATFORM_WINDOWS",
			"CB_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "CB_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CB_DIST"
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
		"%{IncludeDir.src}",
		"%{IncludeDir.vendor}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"ChickenBroth"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CB_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CB_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CB_DIST"
		runtime "Release"
		optimize "On"