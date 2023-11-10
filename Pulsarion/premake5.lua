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
        glew = os.getcwd() .. "/vender/glew/include",
        imgui = os.getcwd() .. "/vender/imgui/imgui"
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

GLEW = {
    static_runtime = true,
    output_dir = "bin/" .. OUTPUT_DIR .. "/GLEW",
    object_dir = "bin-int/" .. OUTPUT_DIR .. "/GLEW"
}

include "vender/glfw"
include "vender/glew"

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
        -- ImGui
        "vender/imgui/imgui/imconfig.h",
        "vender/imgui/imgui/imgui.h",
        "vender/imgui/imgui/imgui_internal.h",
        "vender/imgui/imgui/imgui.cpp",
        "vender/imgui/imgui/imgui_draw.cpp",
        "vender/imgui/imgui/imgui_widgets.cpp",
        "vender/imgui/imgui/imgui_tables.cpp",
        "vender/imgui/imgui/imstb_rectpack.h",
        "vender/imgui/imgui/imstb_textedit.h",
        "vender/imgui/imgui/imstb_truetype.h",
        -- ImGui Backends
        "vender/imgui/imgui/backends/imgui_impl_glfw.h",
        "vender/imgui/imgui/backends/imgui_impl_glfw.cpp",
        "vender/imgui/imgui/backends/imgui_impl_opengl3.h",
        "vender/imgui/imgui/backends/imgui_impl_opengl3.cpp",

    }

    links
    {
        "GLFW",
        "GLEW",
    }

    defines
    {
        "GLEW_STATIC"
    }

    includedirs
    {
        Pulsarion.include_dirs.root,
        Pulsarion.include_dirs.glm,
        Pulsarion.include_dirs.glfw,
        Pulsarion.include_dirs.spdlog,
        Pulsarion.include_dirs.glew,
        Pulsarion.include_dirs.imgui,
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
