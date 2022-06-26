#ifndef MAGE_WREN_MACROS_H
    #define MAGE_WREN_MACROS_H
    #include "wren.hpp"
    // Wren handles
    #define ENSURE_SLOTS(arg) wrenEnsureSlots(vm, arg)
    #define MAKE_HANDLE(arg) wrenMakeCallHandle(vm, arg)
    #define CALL_FUNC(arg) wrenCall(vm, arg)
    #define RELEASE_HANDLE(arg) wrenReleaseHandle(vm, arg)
    // Wren getters
    #define GET_HANDLE(num) wrenGetSlotHandle(vm, num)
    #define GET_VARIABLE(arg1, arg2, num) wrenGetVariable(vm, arg1, arg2, num)   
    #define GET_BOOL(num) wrenGetSlotBool(vm, num)
    #define GET_SLOT_TYPE(num) wrenGetSlotType(vm, num)
    #define GET_USER_DATA() wrenGetUserData(vm);
    // Wren setters
    #define SET_HANDLE(arg, num) wrenSetSlotHandle(vm, num, arg)
    #define SET_NUM(arg, num) wrenSetSlotDouble(vm, num, (double)arg)
#endif