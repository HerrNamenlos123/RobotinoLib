
-- Retrieve the project name
newoption { trigger = "projectname", description = "Name of the generated project" }
local projectName = _OPTIONS["projectname"]
if projectName == nil then print("The project name was not specified! --projectname=YourApplication") end

-- Main Solution
workspace (projectName)
    configurations { "Debug", "Release" }

    platforms { "x64" }
    defaultplatform "x64"
    startproject "RobotinoLib"
    
    filter "system:not windows"
    	location "build"
    filter {}

include "."  -- Import the actual project itself (when it's built on its own)
