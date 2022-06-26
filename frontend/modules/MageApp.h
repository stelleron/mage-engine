#ifndef MAGE_APP_MODULE_H 
    #define MAGE_APP_MODULE_H 
    #define MAGE_APP "mage-app"
    static const char* mageAppModule = 
    "class MageApp {\n"
    "   construct new() {}\n"
    "}\n";
    // Impl. for the Mage App
    VM_FUNC(mageCreateMageApp) {

    }
    DESTRUCT_FUNC(mageDestroyMageApp) {

    }
#endif