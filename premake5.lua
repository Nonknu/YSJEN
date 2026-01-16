workspace "YSJEN"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--INclude directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "YSJEN/vendor/GLFW/include"
IncludeDir["Glad"] = "YSJEN/vendor/Glad/include"
IncludeDir["Imgui"] = "YSJEN/vendor/imgui"
IncludeDir["glm"] = "YSJEN/vendor/glm"
IncludeDir["stb_image"] = "YSJEN/vendor/stb_image"

include "YSJEN/vendor/GLFW"
include "YSJEN/vendor/Glad"
include "YSJEN/vendor/imgui"

project "YSJEN"
    location "YSJEN"
    kind "StaticLib"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "yepch.h"
    pchsource "YSJEN/src/yepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {   
        "YSJEN/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }
    
    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        staticruntime "on"
        systemversion "latest"
        buildoptions "/utf-8"
        
        defines
        {
            "YE_PLATFORM_WINDOWS",
            "YE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "YE_DEBUG"
        runtime "Debug"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "YE_RELEASE"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "YE_DIST"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"

    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"


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
        "YSJEN/vendor/spdlog/include",
        "YSJEN/src",
        "YSJEN/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "YSJEN"
    }

    filter "system:windows"
        staticruntime "on"
        systemversion "latest"
        buildoptions "/utf-8"

        defines
        {
            "YE_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "YE_DEBUG"
        runtime "Debug"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "YE_RELEASE"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "YE_DIST"
        runtime "Release"
        buildoptions "/MD"
        optimize "on"

    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"