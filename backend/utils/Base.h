#ifndef MAGE_BASE_H
    #define MAGE_BASE_H
    // Specifiers for Windows
    #if defined(_WIN32)
        #if defined(BUILD_LIBTYPE_SHARED)
            #define MAGE_API __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
        #elif defined(USE_LIBTYPE_SHARED)
            #define MAGE_API __declspec(dllimport)
        #endif
    #else 
        #define MAGE_API
    #endif
#endif