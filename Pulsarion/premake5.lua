---@diagnostic disable: undefined-field
if (not OUTPUT_DIR) then
    OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
end

if (not PULSARION_CURRENT_DIR) then
    print("PULSARION_CURRENT_DIR must be defined!")
end

if (not PULSARION_LIB_COPY_DIRS) then
    PULSARION_LIB_COPY_DIRS = {}
    print("PULSARION_LIB_COPY_DIRS was not defined, using empty table.")
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
    output_dir = PULSARION_CURRENT_DIR .. "/bin/" .. OUTPUT_DIR .. "/Pulsarion/",
    object_dir = PULSARION_CURRENT_DIR .. "/bin-int/" .. OUTPUT_DIR .. "/Pulsarion/"
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
    staticruntime "off"

    targetdir (Pulsarion.output_dir)
    objdir (Pulsarion.object_dir)

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    links
    {
        "GLFW",
    }

    includedirs
    {
        Pulsarion.include_dirs.root,
        Pulsarion.include_dirs.glm,
        Pulsarion.include_dirs.glfw,
        Pulsarion.include_dirs.spdlog,
    }

    local commands = {}
    for _, dir in ipairs(PULSARION_LIB_COPY_DIRS) do
        local mkdir_command = "{MKDIR} " .. dir
        table.insert(commands, mkdir_command)
        local command = "{COPY} " .. Pulsarion.output_dir .. "/* " .. dir
        table.insert(commands, command)
    end

    postbuildcommands(commands)

    pchheader "Pulsarionpch.h"
    pchsource "src/Pulsarionpch.cpp"
    forceincludes "Pulsarionpch.h"

    filter "action:xcode4"
        pchheader "src/Pulsarionpch.h"
        pchsource "src/Pulsarionpch.cpp"

    filter "system:windows"
        systemversion "latest"

        defines
        {
            Pulsarion.defines.windows,
            "PLS_BUILD_DLL",
        }

        -- Suprress DLL interface warnings
        disablewarnings { "4251" }

    filter "system:linux"
        systemversion "latest"

        defines
        {
            Pulsarion.defines.linux,
            "PLS_BUILD_DLL",
        }

    filter "system:macosx"
        systemversion "10.15"

        defines
        {
            Pulsarion.defines.macos,
            "PLS_BUILD_DLL",
        }

        links
        {
            "Cocoa.framework",
            "OpenGL.framework",
            "CoreFoundation.framework",
            "IOKit.framework",
            "CoreVideo.framework",
   	    }

    filter "configurations:Debug"
        defines {
            "PLS_DEBUG",
            "SPDLOG_ACTIVE_LEVEL=0",
            "_GLIBCXX_DEBUG",
        }
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
