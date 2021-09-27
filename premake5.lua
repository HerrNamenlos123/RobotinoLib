

-- This function defines all compiler options and is called once for debug and once for release
function compilerOptions ()

    includedirs ({ 
        _SCRIPT_DIR .. "/include", 
        _SCRIPT_DIR .. "/modules/spdlog/include",
        "$(ROBOTINOAPI2_64_DIR)/include"
    })

    -- Main source files
    files ({ _SCRIPT_DIR .. "/include/**", _SCRIPT_DIR .. "/src/**" })

    -- Precompiled headers
    --pchheader "Battery/pch.h"
    --pchsource "src/pch.cpp"
    --filter { "files:include/glm/detail/glm.cpp or files:modules/**" }
    --    flags { 'NoPCH' }
    --filter {}

end






-- Retrieve the project name
newoption { trigger = "projectname", description = "Name of the generated project" }
local projectName = _OPTIONS["projectname"]
if projectName == nil then print("The project name was not specified! --projectname=YourApplication") end

-- Main Solution
workspace (projectName)
    configurations { "ALL" }

    platforms { "ALL" }
    defaultplatform "ALL"
    startproject "INSTALL_ALL"

-- Utility project for building and installing everything
project "INSTALL_ALL"
    kind "Utility"
    basedir "build"

    local _includedirs = "$(ProjectDir)../include/;"
    _includedirs = _includedirs .. "$(ProjectDir)../modules/spdlog/include/;"
    _includedirs = _includedirs .. "$(ROBOTINOAPI2_64_DIR)/include;"

    postbuildcommands { 
        "SETX ROBOTINOLIB_INCLUDE_DIRECTORY \"" .. _includedirs .. "\"",
        "SETX ROBOTINOLIB_DEBUG32_LINKS    \"$(ProjectDir)../bin/RobotinoLib32-d.lib;$(ROBOTINOAPI2_64_DIR)/lib/rec_robotino_api2d\"",
        "SETX ROBOTINOLIB_DEBUG64_LINKS    \"$(ProjectDir)../bin/RobotinoLib64-d.lib;$(ROBOTINOAPI2_64_DIR)/lib/rec_robotino_api2\"",
        "SETX ROBOTINOLIB_RELEASE32_LINKS  \"$(ProjectDir)../bin/RobotinoLib32.lib;$(ROBOTINOAPI2_64_DIR)/lib/rec_robotino_api2d\"",
        "SETX ROBOTINOLIB_RELEASE64_LINKS  \"$(ProjectDir)../bin/RobotinoLib64.lib;$(ROBOTINOAPI2_64_DIR)/lib/rec_robotino_api2\""
    }
    
    dependson { projectName .. "-Debug32", projectName .. "-Release32", projectName .. "-Debug64", projectName .. "-Release64" }


-- Debug32 version of the framework
project (projectName .. "-Debug32")
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    location "build/Debug32"
    targetname (projectName .. "32-d")
    targetdir (_SCRIPT_DIR .. "/bin")

    defines { "DEBUG", "_DEBUG" }
    runtime "Debug"
    symbols "On"
    system "Windows"
    architecture "x86"

    -- This is a function defined above
    compilerOptions()


-- Release32 version of the framework
project (projectName .. "-Release32")
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    location "build/Release32"
    targetname (projectName .. "32")
    targetdir (_SCRIPT_DIR .. "/bin")

    defines { "NDEBUG" }
    runtime "Release"
    optimize "On"
    system "Windows"
    architecture "x86"

    -- This is a function defined above
    compilerOptions()



-- Debug64 version of the framework
project (projectName .. "-Debug64")
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    location "build/Debug64"
    targetname (projectName .. "64-d")
    targetdir (_SCRIPT_DIR .. "/bin")

    defines { "DEBUG", "_DEBUG" }
    runtime "Debug"
    symbols "On"
    system "Windows"
    architecture "x86_64"

    -- This is a function defined above
    compilerOptions()


-- Release64 version of the framework
project (projectName .. "-Release64")
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    location "build/Release64"
    targetname (projectName .. "64")
    targetdir (_SCRIPT_DIR .. "/bin")

    defines { "NDEBUG" }
    runtime "Release"
    optimize "On"
    system "Windows"
    architecture "x86_64"

    -- This is a function defined above
    compilerOptions()
