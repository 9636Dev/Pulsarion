---@diagnostic disable: undefined-field
OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

if (not PULSARION_CURRENT_DIR) then
    print("PULSARION_CURRENT_DIR must be defined!")
end

Pulsarion = {
    local_dir = os.getcwd(),
    include_dirs = {
        root = os.getcwd() .. "/src",
        glm = os.getcwd() .. "/vender/glm",
        glfw = os.getcwd() .. "/vender/glfw/include",
        spdlog = os.getcwd() .. "/vender/spdlog/include",
    },
    defines = {
        windows = "PLS_PLATFORM_WINDOWS",
        linux = "PLS_PLATFORM_LINUX",
        macos = "PLS_PLATFORM_MACOS",
    },
    output_dir = PULSARION_CURRENT_DIR .. "/bin/" .. OUTPUT_DIR .. "/Pulsarion",
    object_dir = PULSARION_CURRENT_DIR .. "/bin-int/" .. OUTPUT_DIR .. "/Pulsarion"
}
GLFW = {
    static_runtime = true,
    output_dir = "bin/" .. OUTPUT_DIR .. "/GLFW",
    object_dir = "bin-int/" .. OUTPUT_DIR .. "/GLFW"
}

include "vender/glfw"


project "Pulsarion"
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir (Pulsarion.output_dir)
    objdir (Pulsarion.object_dir)

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        Pulsarion.include_dirs.root,
        Pulsarion.include_dirs.glm,
        Pulsarion.include_dirs.glfw,
        Pulsarion.include_dirs.spdlog,
    }

    pchheader "Pulsarionpch.h"
    pchsource "src/Pulsarionpch.cpp"
    forceincludes "Pulsarionpch.h"

    filter "system:windows"
        systemversion "latest"

        defines
        {
            Pulsarion.defines.windows,
            "PLS_BUILD_DLL",
        }

    filter "system:linux"
        systemversion "latest"

        defines
        {
            Pulsarion.defines.linux,
            "PLS_BUILD_DLL",
        }

    filter "system:macosx"
        systemversion "10.17"

        defines
        {
            Pulsarion.defines.macos,
            "PLS_BUILD_DLL",
        }

    filter "configurations:Debug"
        defines "PLS_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "PLS_RELEASE"
        runtime "Release"
        symbols "off"

    filter "configurations:Dist"
        defines "PLS_DIST"
        runtime "Release"
        symbols "off"
        optimize "on"
