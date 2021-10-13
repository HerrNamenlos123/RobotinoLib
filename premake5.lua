

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
        local _includedirs = _SCRIPT_DIR .. "/include/;"
        _includedirs = _includedirs .. _SCRIPT_DIR .. "/modules/spdlog/include/;"
        _includedirs = _includedirs .. _SCRIPT_DIR .. "/robotinoapi2/windows/include/;"

        postbuildcommands { 
            "SETX ROBOTINOLIB_INCLUDE_DIRECTORY \"" .. _includedirs .. "\"",
            "SETX ROBOTINOLIB_DEBUG_LINKS    \"" .. _SCRIPT_DIR .. "/bin/RobotinoLib-d.lib;" .. _SCRIPT_DIR .. "/robotinoapi2/windows/lib/rec_robotino_api2\"",
            "SETX ROBOTINOLIB_RELEASE_LINKS  \"" .. _SCRIPT_DIR .. "/bin/RobotinoLib-r.lib;" .. _SCRIPT_DIR .. "/robotinoapi2/windows/lib/rec_robotino_api2\"",
            "SETX ROBOTINOLIB_DEPLOY_LINKS   \"" .. _SCRIPT_DIR .. "/bin/RobotinoLib.lib;"   .. _SCRIPT_DIR .. "/robotinoapi2/windows/lib/rec_robotino_api2\"",
            "SETX ROBOTINOLIB_BINARY_DIR     \"" .. _SCRIPT_DIR .. "/robotinoapi2/windows/bin\""
        }
    filter {}
    
    dependson { projectName .. "-Debug", projectName .. "-Release", projectName .. "-Deploy" }


-- Debug version of the framework
project (projectName .. "-Debug")
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    location "build/Debug"
    targetname (projectName .. "-d")
    targetdir (_SCRIPT_DIR .. "/bin")

    defines { "DEBUG", "_DEBUG", "NDEPLOY" }
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
    targetname (projectName .. "-r")
    targetdir (_SCRIPT_DIR .. "/bin")

    defines { "NDEBUG", "NDEPLOY" }
    runtime "Release"
    optimize "On"
    architecture "x86_64"
    
    filter "system:windows"
    	defines { "WIN32" }
    filter {}

    -- This is a function defined above
    compilerOptions()


-- Deploy version of the framework
project (projectName .. "-Deploy")
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    location "build/Deploy"
    targetname (projectName)
    targetdir (_SCRIPT_DIR .. "/bin")

    defines { "NDEBUG", "DEPLOY" }
    runtime "Release"
    optimize "On"
    architecture "x86_64"
    
    filter "system:windows"
        defines { "WIN32" }
    filter {}

    -- This is a function defined above
    compilerOptions()


-- Installation script for linux
filter "system:not windows"
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
filter {}
