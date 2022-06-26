#ifndef MAGE_API_H
    #include <map>
    #include <array>
    #include <utility>
    #include <string>
    #include <string.h>
    #include "wren.hpp"
    #define MAGE_API_H
    // Used to create a Wren class
    class WrenClass {
        private:
            WrenForeignMethodFn allocFn;
            WrenFinalizerFn finalizeFn;
            std::map<std::string, WrenForeignMethodFn> fStaticMethods;
            std::map<std::string, WrenForeignMethodFn> fMethods;
        public:
            WrenClass();
            void addAlloc(WrenForeignMethodFn allocFn);
            void addFinalizer(WrenFinalizerFn finalizeFn);
            void addForeignFn(const char* fnSignature, bool isStatic, WrenForeignMethodFn sourceFn);
            WrenForeignMethodFn searchFn(const char* signature, bool isStatic);
            void getForeignFuncs(WrenForeignClassMethods* fClass);

    };

    // Used to store a Wren-bound library
    class WrenModule {
        private:
            char* currClass;
            std::map<std::string, WrenClass> fClasses;
        public:
            WrenModule(){}
            void addClass(const char* fClass);
            void addForeignAlloc(WrenForeignMethodFn allocFn);
            void addFinalizer(WrenFinalizerFn finalizeFn);
            void addForeignFn(const char* fnSignature, bool isStatic, WrenForeignMethodFn sourceFn);
            WrenForeignMethodFn searchFn(const char* className, bool isStatic, const char* signature);
            void searchFClass(const char* className, WrenForeignClassMethods* fClass);
    };

    // Used to create an entry point for a Wren library
    class WrenLibrary {
        private:
            char* currModule;
            std::map<std::string, WrenModule> fModules;    
        public:        
            WrenLibrary();
            WrenLibrary& declModule(const char* fModule); // Create a new module
            WrenLibrary& declClass(const char* fClass); // Create a new class attached to a module
            WrenLibrary& declForeignAlloc(WrenForeignMethodFn allocFn); // Add a new allocation method
            WrenLibrary& declForeignFinalise(WrenFinalizerFn finalizeFn); // Add a finalizer method
            WrenLibrary& declForeignFn(const char* fnSignature, bool isStatic, WrenForeignMethodFn sourceFn); // Add a foreign method
            WrenForeignMethodFn searchFn(const char* module, const char* className, bool isStatic, const char* signature);
            void searchFClass(const char* module, const char* className, WrenForeignClassMethods* fClass);
    };
#endif