

-- This function defines all compiler options and is called once for debug and once for release
function compilerOptions ()

    includedirs (_SCRIPT_DIR .. "/include")
    includedirs (_SCRIPT_DIR .. "/modules/spdlog/include")
    
    filter "system:windows"
    	includedirs ("$(ROBOTINOAPI2_64_DIR)/include")
    filter "system:not windows"
    	includedirs (_SCRIPT_DIR .. "/robotinoapi2/linux/include")
    filter {}

    -- Main source files
    files ({ _SCRIPT_DIR .. "/include/**", _SCRIPT_DIR .. "/src/**" })

    -- Precompiled headers
    --pchheader "Robotino/pch.h"
    --pchsource "src/pch.cpp"
    --filter { "files:modules/**" }
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
    startproject "BUILD_ALL"
    
    filter "system:not windows"
    	location "build"
    filter {}

-- Utility project for building and installing everything
project "BUILD_ALL"
    kind "Utility"
    basedir "build/BUILD_ALL"

    filter "system:windows"
        local _includedirs = "$(ProjectDir)../include/;"
        _includedirs = _includedirs .. "$(ProjectDir)../modules/spdlog/include/;"
        _includedirs = _includedirs .. "$(ROBOTINOAPI2_64_DIR)/include;"

        postbuildcommands { 
            "SETX ROBOTINOLIB_INCLUDE_DIRECTORY \"" .. _includedirs .. "\"",
            "SETX ROBOTINOLIB_DEBUG_LINKS    \"$(ProjectDir)../bin/RobotinoLib-d.lib;$(ROBOTINOAPI2_64_DIR)/lib/rec_robotino_api2\"",
            "SETX ROBOTINOLIB_RELEASE_LINKS  \"$(ProjectDir)../bin/RobotinoLib.lib;$(ROBOTINOAPI2_64_DIR)/lib/rec_robotino_api2\""
        }
    filter {}
    
    dependson { projectName .. "-Debug", projectName .. "-Release" }


-- Debug version of the framework
project (projectName .. "-Debug")
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    location "build/Debug"
    targetname (projectName .. "-d")
    targetdir (_SCRIPT_DIR .. "/bin")

    defines { "DEBUG", "_DEBUG" }
    runtime "Debug"
    symbols "On"
    architecture "x86_64"
    
    filter "system:windows"
    	defines { "WIN32" }
    filter {}

    -- This is a function defined above
    compilerOptions()


-- Release version of the framework
project (projectName .. "-Release")
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    location "build/Release"
    targetname (projectName)
    targetdir (_SCRIPT_DIR .. "/bin")

    defines { "NDEBUG" }
    runtime "Release"
    optimize "On"
    architecture "x86_64"
    
    filter "system:windows"
    	defines { "WIN32" }
    filter {}

    -- This is a function defined above
    compilerOptions()


newaction {
    trigger     = "install",
    description = "Install the software",
    execute = function ()
        print("{COPY} " .. _MAIN_SCRIPT_DIR .. "/robotinoapi2/linux/include/ /usr/local/")
        os.execute("{COPY} " .. _MAIN_SCRIPT_DIR .. "/robotinoapi2/linux/include/ /usr/local/")

        print("{COPY} " .. _MAIN_SCRIPT_DIR .. "/robotinoapi2/linux/bin/ /usr/local/")
        os.execute("{COPY} " .. _MAIN_SCRIPT_DIR .. "/robotinoapi2/linux/bin/ /usr/local/")

        print("{COPY} " .. _MAIN_SCRIPT_DIR .. "/include/ /usr/local/")
        os.execute("{COPY} " .. _MAIN_SCRIPT_DIR .. "/include/ /usr/local/")

        print("{COPY} " .. _MAIN_SCRIPT_DIR .. "/bin/ /usr/local/")
        os.execute("{COPY} " .. _MAIN_SCRIPT_DIR .. "/bin/ /usr/local/")

        print("{COPY} " .. _MAIN_SCRIPT_DIR .. "/modules/spdlog/include/ /usr/local/")
        os.execute("{COPY} " .. _MAIN_SCRIPT_DIR .. "/modules/spdlog/include/ /usr/local/")
    end
}
