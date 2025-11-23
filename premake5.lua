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

include "YSJEN/vendor/GLFW"
include "YSJEN/vendor/Glad"
include "YSJEN/vendor/imgui"

project "YSJEN"
    location "YSJEN"
    kind "SharedLib"
    language "C++"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "yepch.h"
    pchsource "YSJEN/src/yepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }

    includedirs
    {   
        "YSJEN/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Imgui}",
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
        staticruntime "On"
        systemversion "latest"
        buildoptions "/utf-8"
        
        defines
        {
            "YE_PLATFORM_WINDOWS",
            "YE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
    
    filter "configurations:Debug"
        defines "YE_DEBUG"
        runtime "Debug"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "YE_RELEASE"
        runtime "Release"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "YE_DIST"
        runtime "Release"
        buildoptions "/MD"
        optimize "On"

    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"


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
        cppdialect "C++17"
        staticruntime "On"
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
        symbols "On"

    filter "configurations:Release"
        defines "YE_RELEASE"
        runtime "Release"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "YE_DIST"
        runtime "Release"
        buildoptions "/MD"
        optimize "On"

    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"