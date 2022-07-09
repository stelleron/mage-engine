#ifndef MAGE_APP_MODULE_H 
    #define MAGE_APP_MODULE_H 
    #define MAGE_APP "mage-app"
    static const char* mageAppModule = 
    "foreign class NativeApp {\n"
    "   construct new(config) {}\n"
    "}\n"
    "foreign class MageConfig {\n"
    "   construct new() {}\n"
    "}\n"
    "class MageApp {\n" // MageApp is a wrapper over the native application
    "   construct new(config) {\n"
    "       _mage = NativeApp.new(config)\n"
    "   }\n"
    "}\n";
    // Impl. for the MageApp declared as NativeApp
    VM_FUNC(mageCreateMageApp) {
        MageEngine* engine = SET_FOREIGN(MageEngine);
        MageConfig* config = (MageConfig*)GET_FOREIGN(1);
        new (engine) MageEngine(config);
    }
    DESTRUCT_FUNC(mageDestroyMageApp) {
        CALL_DESTRUCTOR(MageEngine);
    }
    // Impl. for the MageConfig 
    VM_FUNC(mageCreateMageConfig) {
        MageConfig* config = (MageConfig*)SET_FOREIGN(MageConfig);
        new (config) MageConfig();
    }
    DESTRUCT_FUNC(mageDestroyMageConfig) {
        CALL_DESTRUCTOR(MageConfig);
    }
#endif