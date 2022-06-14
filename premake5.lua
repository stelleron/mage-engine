-- premake5.lua
workspace "MageEngine"
    architecture "x64"
    configurations {"Debug", "Release"} 

project "mage"
    kind "SharedLib"
    language "C++"
    cppdialect "C++17"

    targetdir "build/"
    objdir "build/obj/backend/"

    files {"backend/**.cpp", "backend/utils/**.cpp", "backend/modules/window/**.cpp"}
    includedirs {"external/include/", "backend/" , "backend/modules/"}
    libdirs {"external/lib/"}
    links {"whereami", "spdlog", "glfw3", "glad", "GLUT.framework", 
    "CoreVideo.framework", "IOKit.framework", "OpenGL.framework", "Cocoa.framework"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

project "exec"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "build/"
    objdir "build/obj/frontend/"

    files {"frontend/**.cpp", "frontend/wren/**.cpp", "external/lib/wren.c"}
    includedirs {"backend/", "external/include/", "backend/modules/"}
    libdirs {"build/"}
    links {"mage"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
    
