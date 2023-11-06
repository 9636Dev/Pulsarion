OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
PULSARION_CURRENT_DIR = os.getcwd()
PULSARION_LIB_COPY_DIRS = {
    PULSARION_CURRENT_DIR .. "/bin/" .. OUTPUT_DIR .. "/PulsarionExamples",
}

workspace "Pulsarion"
    configurations { "Debug", "Release", "Dist" }
    architecture "x86_64"
    startproject "PulsarionExamples"

    include "Pulsarion"

    project "PulsarionExamples"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. OUTPUT_DIR .. "/%{prj.name}")
        objdir ("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

        files
        {
            "examples/**.h",
            "examples/**.cpp",
        }

        includedirs
        {
            "examples",
            Pulsarion.include_dirs.root,
            Pulsarion.include_dirs.glm,
            Pulsarion.include_dirs.glfw,
        }

        links
        {
            "Pulsarion",
        }

        filter "system:windows"
            systemversion "latest"

            defines
            {
                Pulsarion.defines.windows,
            }

        filter "system:linux"
            systemversion "latest"

            defines
            {
                Pulsarion.defines.linux,
            }

        filter "system:macosx"
            systemversion "10.17"

            defines
            {
                Pulsarion.defines.macos,
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
            optimize "on"

        filter "configurations:Dist"
            defines "PLS_DIST"
            runtime "Release"
            optimize "on"
