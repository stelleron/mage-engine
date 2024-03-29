#include "wren/WrenAPI.hpp"
#include <string.h>
#include "utils/DebugTools.hpp"

namespace mage {
    // Impl. for the Wren foreign library class and sub classes
    WrenLibrary::WrenLibrary() {
        
    }

    WrenLibrary& WrenLibrary::declModule(const char* fModule) {
        currModule = (char*)fModule;
        fModules.insert(std::pair<char*, WrenModule>(currModule, WrenModule() ));
        return *this;
    }

    WrenLibrary& WrenLibrary::declClass(const char* fClass) {
        // First find the current module, then attach a new class to it
        auto mod = fModules.find(currModule);
        if (mod == fModules.end()) {
            MAGE_ERROR("[Frontend] {0} module does not exist", currModule);
        }
        else {
            mod->second.addClass(fClass);
        }
        return *this;
    }

    WrenLibrary& WrenLibrary::declForeignAlloc(WrenForeignMethodFn allocFn) {
        // First find the current module, then attach a new class to it
        auto mod = fModules.find(currModule);
        if (mod == fModules.end()) {
            MAGE_ERROR("[Frontend] {0} module does not exist", currModule);
        }
        else {
            mod->second.addForeignAlloc(allocFn);
        }
        return *this;
    }

    WrenLibrary& WrenLibrary::declForeignFinalise(WrenFinalizerFn finalizeFn) {
        auto mod = fModules.find(currModule);
        if (mod == fModules.end()) {
            MAGE_ERROR("[Frontend] {0} module does not exist", currModule);
        }
        else {
            mod->second.addFinalizer(finalizeFn);
        }
        return *this;
    }

    WrenLibrary& WrenLibrary::declForeignFn(const char* fnSignature, bool isStatic, 
                                            WrenForeignMethodFn sourceFn) {
        auto mod = fModules.find(currModule);
        if (mod == fModules.end()) {
            MAGE_ERROR("[Frontend] {0} module does not exist", currModule);
        }
        else {
            mod->second.addForeignFn(fnSignature, isStatic, sourceFn);
        }
        return *this;
    }

    WrenForeignMethodFn WrenLibrary::searchFn(const char* module, const char* className, 
                                            bool isStatic, const char* signature) {
        // First get the module the foreign function is called from
        auto mod = fModules.find(std::string(module));
        if (mod == fModules.end()) {
            MAGE_ERROR("[Frontend] {0} module does not exist", module);
            return fModules.begin()->second.searchFn(className, isStatic, signature);
        }
        else {
            // Return the function from the given module
            return mod->second.searchFn(className, isStatic, signature);
        }
    }

    void WrenLibrary::searchFClass(const char* module, const char* className, WrenForeignClassMethods* fClass) {
        // First get the module the foreign function is called from
        auto mod = fModules.find(std::string(module));
        if (mod == fModules.end()) {
            MAGE_ERROR("[Frontend] {0} module does not exist", module);
        }
        else {
            // Return the function from the given module
            mod->second.searchFClass(className, fClass);
        }

    }

    void WrenModule::addClass(const char* fClass){
        currClass = (char*)fClass;
        fClasses.insert(std::pair<char*, WrenClass>((char*)fClass, WrenClass()));
    }

    void WrenModule::addForeignAlloc(WrenForeignMethodFn allocFn) {
        auto fClass = fClasses.find(currClass);
        if (fClass == fClasses.end()) {
            MAGE_ERROR("[Frontend] {0} class does not exist", currClass);
        }
        else {
            fClass->second.addAlloc(allocFn);
        }
    }

    void WrenModule::addFinalizer(WrenFinalizerFn finalizeFn) {
        auto fClass = fClasses.find(currClass);
        if (fClass == fClasses.end()) {
            MAGE_ERROR("[Frontend] {0} class does not exist", currClass);
        }
        else {
            fClass->second.addFinalizer(finalizeFn);
        }
    }

    void WrenModule::addForeignFn(const char* fnSignature, bool isStatic, WrenForeignMethodFn sourceFn) {
        auto fClass = fClasses.find(currClass);
        if (fClass == fClasses.end()) {
            MAGE_ERROR("[Frontend] {0} class does not exist", currClass);
        }
        else {
            fClass->second.addForeignFn(fnSignature, isStatic, sourceFn);
        } 
    }

    WrenForeignMethodFn WrenModule::searchFn(const char* className, bool isStatic, const char* signature) {
        auto fClass = fClasses.find(std::string(className));
        if (fClass == fClasses.end()) {
            MAGE_ERROR("[Frontend] {0} class does not exist", className);
            return fClasses.begin()->second.searchFn(signature, isStatic);
        }
        else {
            return fClass->second.searchFn(signature, isStatic);
        } 
    }

    void WrenModule::searchFClass(const char* className, WrenForeignClassMethods* fClass) {
        auto fClassName = fClasses.find(std::string(className));
        if (fClassName == fClasses.end()) {
            MAGE_ERROR("[Frontend] {0} class does not exist", className);
        }
        else {
            fClassName->second.getForeignFuncs(fClass);
        } 
    }

    WrenClass::WrenClass() {
        allocFn = NULL;
        finalizeFn = NULL;
    }

    void WrenClass::addAlloc(WrenForeignMethodFn allocFn) {
        this->allocFn = allocFn;
    }

    void WrenClass::addFinalizer(WrenFinalizerFn finalizeFn) {
        this->finalizeFn = finalizeFn;
    }

    void WrenClass::addForeignFn(const char* fnSignature, bool isStatic, WrenForeignMethodFn sourceFn) {
        if (isStatic) {
            fStaticMethods.insert(std::pair<char*, WrenForeignMethodFn>((char*)fnSignature, sourceFn));
        }
        else {
            fMethods.insert(std::pair<char*, WrenForeignMethodFn>((char*)fnSignature, sourceFn));
        }
    }

    WrenForeignMethodFn WrenClass::searchFn(const char* signature, bool isStatic) {
        if (isStatic) {
            auto func = fStaticMethods.find(std::string(signature));
            if (func == fStaticMethods.end()) {
                MAGE_ERROR("[Frontend] {0} function does not exist", signature);
                return fStaticMethods.begin()->second;
            }
            else {
                return func->second;
            } 
        }
        else {
            auto func = fMethods.find(std::string(signature));
            if (func == fMethods.end()) {
                MAGE_ERROR("[Frontend] {0} function does not exist", signature);
                return fMethods.begin()->second;
            }
            else {
                return func->second;
            } 
        }
    }

    void WrenClass::getForeignFuncs(WrenForeignClassMethods* fClass) {
        fClass->allocate = allocFn;
        fClass->finalize = finalizeFn;
    }
}