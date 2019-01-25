function win_sdk_version()
    local reg_arch = iif( os.is64bit(), "\\Wow6432Node\\", "\\" )
    local sdk_version = os.getWindowsRegistry( "HKLM:SOFTWARE" .. reg_arch .."Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion" )
    if sdk_version ~= nil then return sdk_version end
end

function include_sfml()
    includedirs "external/SFML/include/"
end	
    
function link_sfml()
    libdirs "external/SFML/lib/x64/"
        
    filter { "configurations:debug", "kind:not StaticLib" }
        links { 
            "sfml-graphics-d.lib",
            "sfml-window-d.lib",
            "sfml-audio-d.lib",
            "sfml-network-d.lib",
            "sfml-system-d.lib" }

    filter { "configurations:release", "kind:not StaticLib" }
    links { 
        "sfml-graphics.lib",
        "sfml-window.lib",
        "sfml-audio.lib",
        "sfml-network.lib",
        "sfml-system.lib" }

    filter {}
end

workspace "undies"
    location "solution"
    language "C++"

    startproject "engine"
	
	architecture "x86_64"
    configurations { "debug", "release" }

	filter { "configurations:debug", "system:windows", "action:vs*"}
        symbols "On"
        targetdir "builds/debug"
        systemversion(win_sdk_version() .. ".0")
        objdir "builds/debug/obj/%{prj.name}/%{cfg.longname}"
	
	filter { "configurations:release", "system:windows", "action:vs*"}
        optimize "On"
        targetdir "builds/release"
        systemversion(win_sdk_version() .. ".0")
        objdir "builds/release/obj/%{prj.name}/%{cfg.longname}"

    filter { }

    -- Copy files (DEBUG)
    os.copyfile("external/SFML/lib/x64/sfml-graphics-d.dll", "builds/debug/sfml-graphics-d.dll")
    os.copyfile("external/SFML/lib/x64/sfml-window-d.dll", "builds/debug/sfml-window-d.dll")
    os.copyfile("external/SFML/lib/x64/sfml-audio-d.dll", "builds/debug/sfml-audio-d.dll")
    os.copyfile("external/SFML/lib/x64/sfml-network-d.dll", "builds/debug/sfml-network-d.dll")
    os.copyfile("external/SFML/lib/x64/sfml-system-d.dll", "builds/debug/sfml-system-d.dll")

    -- Copy files (RELEASE)
    os.copyfile("external/SFML/lib/x64/sfml-graphics.dll", "builds/release/sfml-graphics.dll")
    os.copyfile("external/SFML/lib/x64/sfml-window.dll", "builds/release/sfml-window.dll")
    os.copyfile("external/SFML/lib/x64/sfml-audio.dll", "builds/release/sfml-audio.dll")
    os.copyfile("external/SFML/lib/x64/sfml-network.dll", "builds/release/sfml-network.dll")
    os.copyfile("external/SFML/lib/x64/sfml-system.dll", "builds/release/sfml-system.dll")

project "engine"
    kind "SharedLib"
    location "source/engine"
    files { "source/engine/**.hpp", "source/engine/**.cpp" }

    defines "ENGINE_API_DLL_EXPORT"

    include_sfml()
    link_sfml()

function use_engine()
    includedirs "source/engine"
    filter "kind:not StaticLib"
        links "engine"
    
    filter {}
    
    include_sfml()
    link_sfml()
end

project "game"
    kind "SharedLib"
    location "source/game"
    files { "source/game/**.hpp", "source/game/**.cpp" }
    use_engine()
