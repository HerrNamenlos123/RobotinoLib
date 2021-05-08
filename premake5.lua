
-- Main Project declaration
project "RobotinoLib"
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
    location "build"

    -- Local paths
    local includes = { _SCRIPT_DIR .. "/include" }
    local sources = { _SCRIPT_DIR .. "/include/**", _SCRIPT_DIR .. "/src/**" }
    local outputdir = _SCRIPT_DIR .. "/bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    local link = {}

    -- Add paths to the higher level instance (top level project)
    for _,v in ipairs(includes) do table.insert(IncludeDirs, v) end
    for _,v in ipairs(sources) do table.insert(SourceFiles, v) end
    table.insert(LibraryDirs, outputdir)
    table.insert(Links, link)

    ---- Main source files
    includedirs (includes)
    files (sources)
    targetdir (outputdir)
    links (link)

    -- Organize the files in the Visual Studio project view
    vpaths {
        ["include"] = { _SCRIPT_DIR .. "/include/**" },
        ["src"] = { _SCRIPT_DIR .. "/src/**" }
    }

    -- Configuration filters, filters are active up to the next filter statement
    -- Indentation is purely visual
    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"

    filter { "platforms:Win32" }
        system "Windows"
        architecture "x86"

    filter { "platforms:x64" }
        system "Windows"
        architecture "x86_64"

