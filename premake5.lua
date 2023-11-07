OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
PULSARION_CURRENT_DIR = os.getcwd()
PULSARION_LIB_COPY_DIRS = {
    PULSARION_CURRENT_DIR .. "/bin/" .. OUTPUT_DIR .. "/PulsarionExamples/",
    PULSARION_CURRENT_DIR .. "/bin/" .. OUTPUT_DIR .. "/PulsarionTests/"
}

workspace "Pulsarion"
    configurations { "Debug", "Release", "Dist" }
    architecture "x86_64"
    startproject "PulsarionExamples"

    include "Pulsarion"

    project "PulsarionExamples"
        location "examples"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"

        targetdir ("bin/" .. OUTPUT_DIR .. "/%{prj.name}/")
        objdir ("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}/")

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
            systemversion "10.15"

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

    project "PulsarionTests"
        location "tests"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"

        targetdir ("bin/" .. OUTPUT_DIR .. "/%{prj.name}/")
        objdir ("bin-int/" .. OUTPUT_DIR .. "/%{prj.name}/")

        files
        {
            "tests/**.h",
            "tests/**.cpp",
        }

        includedirs
        {
            "tests",
            Pulsarion.include_dirs.root,
            Pulsarion.include_dirs.glm,
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
            systemversion "10.15"

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