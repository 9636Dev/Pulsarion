if (not GLEW) then
    GLEW = {
        static_runtime = true,
        output_dir = "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/GLEW",
		object_dir = "bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/GLEW"
    }
else
   
    if (GLEW.static_runtime == nil) then
        GLEW.static_runtime = true
    end
    GLEW.output_dir = GLEW.output_dir or "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/GLEW"
    GLEW.object_dir = GLEW.object_dir or "bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/GLEW"
end

project "GLEW"
	kind "StaticLib"
	language "C"
    if GLEW.static_runtime then
	    staticruntime "on"
    end

	targetdir (GLEW.output_dir)
	objdir (GLEW.object_dir)

	files
	{
        "include/GL/glew.h",
		"src/glew.c",
	}

	defines
	{
		"GLEW_STATIC"
	}

	includedirs 
	{
		"include"
	}

	filter "action:vs*"
		buildoptions { "/wd4996", "/wd4133" }

	filter "system:linux"
		systemversion "latest"

	filter "system:windows"
		systemversion "latest"

    filter "system:macosx"
        systemversion "10.13"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
          symbols "off"
