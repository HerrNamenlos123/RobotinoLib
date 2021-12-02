
-- Check if an environment variable exists, otherwise abort the program
function CheckEnvVar (variable, productName)
    if (os.getenv(variable) == nil) then
        print("Environment variable " .. variable .. " not found! Make sure the " .. productName .. " is installed correctly!")
        projectName = nil
    end
end

-- Here check if the Festo Robotino API 2 is installed, otherwise abort
if os.host() == "windows" then
    CheckEnvVar("ROBOTINOAPI2_64_DIR", "Festo Robotino API 2")
end

-- The actual project file itself
project "RobotinoLib"
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    architecture "x86_64"
    targetname "RobotinoLib"
    location "build"

    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        runtime "Debug"
        symbols "On"
        targetdir (_SCRIPT_DIR .. "/bin/Debug/")
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"
        targetdir (_SCRIPT_DIR .. "/bin/Release/")
    filter {}

    includedirs (_SCRIPT_DIR .. "/include")
    includedirs (_SCRIPT_DIR .. "/modules/spdlog/include")
    
    filter "system:windows"
        includedirs ("$(ROBOTINOAPI2_64_DIR)/include")
    	defines { "WIN32" }
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

        print("echo \"/usr/local/bin\" | sudo tee -a /etc/ld.so.conf.d/RobotinoLib.conf; sudo ldconfig")
        os.execute("echo \"/usr/local/bin\" | sudo tee -a /etc/ld.so.conf.d/RobotinoLib.conf; sudo ldconfig")
    end
}
filter {}
