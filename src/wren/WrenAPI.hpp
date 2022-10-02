#ifndef MAGE_WRENAPI_HPP
    #define MAGE_WRENAPI_HPP
    #include <map>
    #include <array>
    #include <utility>
    #include <string>
    #include "wren.hpp"

    namespace mage {

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
        // Macros
        // Wren handles
        #define ENSURE_SLOTS(arg) wrenEnsureSlots(vm, arg)
        #define MAKE_HANDLE(arg) wrenMakeCallHandle(vm, arg)
        #define CALL_FUNC(arg) wrenCall(vm, arg)
        #define RELEASE_HANDLE(arg) wrenReleaseHandle(vm, arg)
        // Wren getters
        #define GET_HANDLE(num) wrenGetSlotHandle(vm, num)
        #define GET_VARIABLE(arg1, arg2, num) wrenGetVariable(vm, arg1, arg2, num)   
        #define GET_BOOL(num) wrenGetSlotBool(vm, num)
        #define GET_INT(num) (int)wrenGetSlotDouble(vm, num)
        #define GET_FLOAT(num) (float)wrenGetSlotDouble(vm, num)
        #define GET_SLOT_TYPE(num) wrenGetSlotType(vm, num)
        #define GET_USER_DATA() wrenGetUserData(vm);
        #define GET_FOREIGN(num) wrenGetSlotForeign(vm, num)
        #define GET_STR(num) wrenGetSlotString(vm, num)
        // Wren setters
        #define SET_BOOL(arg, num) wrenSetSlotBool(vm, num, arg)
        #define SET_HANDLE(arg, num) wrenSetSlotHandle(vm, num, arg)
        #define SET_NUM(arg, num) wrenSetSlotDouble(vm, num, (double)arg)
        #define SET_FOREIGN(class) (class*)wrenSetSlotNewForeign(vm, 0, 0, sizeof(class))
        #define SET_USER_DATA(arg) wrenSetUserData(vm, arg)
        // Wren foreign function headers
        #define VM_FUNC(func) void func(WrenVM* vm)
        #define DESTRUCT_FUNC(arg) void arg(void* data)
        // Misc.
        #define CALL_DESTRUCTOR(arg) arg* ptr = (arg*)data; ptr->~arg()
    }
#endif