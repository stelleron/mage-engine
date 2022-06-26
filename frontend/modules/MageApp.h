#ifndef MAGE_APP_MODULE_H 
    #define MAGE_APP_MODULE_H 
    #define MAGE_APP "mage-app"
    static const char* mageAppModule = 
    "foreign class NativeApp {\n"
    "   construct new() {}\n"
    "}\n"
    "class MageApp {\n"
    "   construct new() {\n"
    "       _mage = NativeApp.new()\n"
    "   }\n"
    "}\n";
    // Impl. for the MageApp declared as NativeApp
    VM_FUNC(mageCreateMageApp) {
        MageEngine* engine = (MageEngine*)SET_FOREIGN(MageEngine);
        engine =  new MageEngine();
    }
    DESTRUCT_FUNC(mageDestroyMageApp) {
        delete (MageEngine*)data;
    }
#endif