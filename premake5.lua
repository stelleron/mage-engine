-- premake5.lua
workspace "MageEngine"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"} -- Debug is used during the design of the backend, Release is for writing games in Wren and Dist is for publishing

project "mage"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "build/"
    objdir "build/obj/"

    files {"source/**.cpp", "source/utils/**.cpp", "source/frontend/**.cpp", "external/lib/wren.c"}
    includedirs {"external/include/", "source/"}
    libdirs {"external/lib/"}
    links {"whereami", "spdlog", "glfw3", "glad", "datapak", "GLUT.framework", 
    "CoreVideo.framework", "IOKit.framework", "OpenGL.framework", "Cocoa.framework"}

    filter "configurations:Debug"
        defines { "DEBUG", "DEVBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "DEBUG" }
        optimize "On"

    filter "configurations:Dist"
        defines { "NDEBUG" }
        optimize "On"