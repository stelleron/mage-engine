-- premake5.lua
workspace "MageEngine"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"} -- Debug is used during the design of the backend, Release is for writing games in Wren and Dist is for publishing

project "mage"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"

    targetdir "build/"
    objdir "build/obj/backend/"

    files {"backend/**.cpp", "backend/utils/**.cpp", "backend/modules/window/**.cpp", "external/lib/wren.c"}
    includedirs {"external/include/", "backend/" , "backend/modules/"}
    libdirs {"external/lib/"}
    links {"whereami", "spdlog", "glfw3", "glad", "GLUT.framework", 
    "CoreVideo.framework", "IOKit.framework", "OpenGL.framework", "Cocoa.framework"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "DEBUG" }
        optimize "On"

    filter "configurations:Dist"
        defines { "NDEBUG" }
        optimize "On"

project "exec"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "build/"
    objdir "build/obj/frontend/"

    files {"frontend/**.cpp", "frontend/wren/**.cpp"}
    includedirs {"backend/", "external/include/", "backend/modules/", "frontend/"}
    libdirs {"build/"}
    links {"mage"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "DEBUG" }
        optimize "On"

    filter "configurations:Dist"
        defines { "NDEBUG" }
        optimize "On"
    
