function win_sdk_version()
    local reg_arch = iif( os.is64bit(), "\\Wow6432Node\\", "\\" )
    local sdk_version = os.getWindowsRegistry( "HKLM:SOFTWARE" .. reg_arch .."Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion" )
    if sdk_version ~= nil then return sdk_version end
end

function include_sfml()
    includedirs "external/SFML/include/"
end	

function include_glm()
    includedirs "external/GLM/include/"
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
    os.copyfile("external/SFML/lib/x64/openal32.dll", "builds/debug/openal32.dll")
    os.copyfile("external/SFML/lib/x64/sfml-graphics-d-2.dll", "builds/debug/sfml-graphics-d-2.dll")
    os.copyfile("external/SFML/lib/x64/sfml-window-d-2.dll", "builds/debug/sfml-window-d-2.dll")
    os.copyfile("external/SFML/lib/x64/sfml-audio-d-2.dll", "builds/debug/sfml-audio-d-2.dll")
    os.copyfile("external/SFML/lib/x64/sfml-network-d-2.dll", "builds/debug/sfml-network-d-2.dll")
    os.copyfile("external/SFML/lib/x64/sfml-system-d-2.dll", "builds/debug/sfml-system-d-2.dll")

    -- Copy files (RELEASE)
    os.copyfile("external/SFML/lib/x64/openal32.dll", "builds/release/openal32.dll")
    os.copyfile("external/SFML/lib/x64/sfml-graphics-2.dll", "builds/release/sfml-graphics-2.dll")
    os.copyfile("external/SFML/lib/x64/sfml-window-2.dll", "builds/release/sfml-window-2.dll")
    os.copyfile("external/SFML/lib/x64/sfml-audio-2.dll", "builds/release/sfml-audio-2.dll")
    os.copyfile("external/SFML/lib/x64/sfml-network-2.dll", "builds/release/sfml-network-2.dll")
    os.copyfile("external/SFML/lib/x64/sfml-system-2.dll", "builds/release/sfml-system-2.dll")

project "engine"
    kind "SharedLib"
    location "source/engine"
    files { "source/engine/**.hpp", "source/engine/**.cpp" }

    defines "ENGINE_API_DLL_EXPORT"

    include_sfml()
    link_sfml()
    include_glm()

function use_engine()
    includedirs "source/engine"
    filter "kind:not StaticLib"
        links "engine"
    
    filter {}
    
    include_sfml()
    link_sfml()
end

project "game"
    kind "ConsoleApp"
    location "source/game"
    files { "source/game/**.hpp", "source/game/**.cpp" }
    use_engine()
