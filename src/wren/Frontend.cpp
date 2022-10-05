#include "wren/Frontend.hpp"
#include "utils/DebugTools.hpp"
#include <iostream>

namespace mage {
    // MAGE Engine modules
    const char* mageUtilsModule =
    "foreign class Vec2{\n"
    "   construct new(x,y){}\n"
    "   foreign x\n"
    "   foreign y\n"
    "   foreign x=(value)\n"
    "   foreign y=(value)\n"
    "}\n"
    "foreign class Vec3{\n"
    "   construct new(x,y,z){}\n"
    "   foreign x\n"
    "   foreign y\n"
    "   foreign z\n"
    "   foreign x=(value)\n"
    "   foreign y=(value)\n"
    "   foreign z=(value)\n"
    "}\n"
    "foreign class Vec4{\n"
    "   construct new(x,y,z,w){}\n"
    "   foreign x\n"
    "   foreign y\n"
    "   foreign z\n"
    "   foreign w\n"
    "   foreign x=(value)\n"
    "   foreign y=(value)\n"
    "   foreign z=(value)\n"
    "   foreign w=(value)\n"
    "}\n"
    "foreign class Color{\n"
    "   construct new(r,g,b,a){}\n"
    "   static rgb(r,g,b){ Color.new(r,g,b,255) }\n"
    "   static rgba(r,g,b,a){ Color.new(r,g,b,a) }\n"
    "   static normal_rgb(r,g,b){ Color.new(r/255, g/255, b/255, 1.0) }\n"
    "   static normal_rgba(r,g,b,a){ Color.new(r/255, g/255, b/255, a/255) }\n"
    "   \n"
    "   foreign r\n"
    "   foreign g\n"
    "   foreign b\n"
    "   foreign a\n"
    "   foreign r=(value)\n"
    "   foreign g=(value)\n"
    "   foreign b=(value)\n"
    "   foreign a=(value)\n"
    "}\n";

    const char* mageRandomModule = 
    "class Random {\n"
    "   foreign static generate()\n"
    "   foreign static generate(min, max)\n"
    "   foreign static seed=(value)\n"
    "}\n"
    ;

    const char* mageWindowModule =
    "import \"mage-utils\" for Vec2\n"
    "class Window {\n"
    "   construct new() {}\n"
    "   foreign wasResized \n"
    "   foreign wasMoved \n"
    "   foreign isMinimized \n"
    "   foreign isMaximized \n"
    "   foreign pos=(value)\n"
    "   foreign x\n"
    "   foreign y\n"
    "   pos {Vec2.new(this.x, this.y)}\n"
    "   foreign width\n"
    "   foreign height\n"
    "   foreign restore()\n"
    "   foreign minimize()\n"
    "   foreign maximize()\n"
    "   foreign title=(value)\n"
    "   foreign close()\n"
    "}\n"
    ;

    const char* mageTimerModule = 
    "foreign class Timer {\n"
    "   construct new() {}\n"
    "   foreign reset()\n"
    "   foreign elapsed\n"
    "   foreign elapsedMillis\n"
    "}\n"
    "class InternalClock {\n"
    "   construct new() {}\n"
    "   foreign dt\n"
    "   foreign fps\n"
    "}\n"
    ;

    const char* mageGeometryModule = 
    "import \"mage-utils\" for Vec2\n"
    "foreign class Point {\n"
    "   construct new(x, y) {}\n"
    "   foreign x\n"
    "   foreign y\n"
    "   pos {Vec2.new(this.x, this.y)}\n"
    "   foreign pos=(value)\n"
    "}\n"
    "foreign class Line {\n"
    "   construct new(start, end) {}\n"
    "   foreign startX\n"
    "   foreign startY\n"
    "   foreign endX\n"
    "   foreign endY\n"
    "   startPos {Vec2.new(this.startX, this.startY)}\n"
    "   endPos {Vec2.new(this.endX, this.endY)}\n"
    "   foreign startPos=(value)\n"
    "   foreign endPos=(value)\n"
    "}\n"
    ;

    const char* mageCameraModule = 
    "import \"mage-utils\" for Vec2\n"
    "class Camera {\n"
    "   construct new() {}\n"
    "   foreign xoffset\n"
    "   foreign yoffset\n"
    "   offset {Vec2.new(this.xoffset, this.yoffset)}\n"
    "   foreign zoom\n"
    "   foreign rotation\n"
    "   foreign offset=(value)\n"
    "   foreign zoom=(value)\n"
    "   foreign rotation=(value)\n"
    "}\n"
    ;

    const char* mageResModule =
    "class Filesystem{\n"
    "   foreign static cwd=(value)\n"
    "   foreign static dirExists(path)\n"
    "   foreign static fileExists(path)\n"
    "   foreign static load(path)\n"
    "   foreign static save(path, str)\n"
    "}\n"
    "foreign class Image {\n"
    "   construct load(path) {}\n"
    "   foreign width\n"
    "   foreign height\n"
    "   static RGB{1}\n"
    "   static RGBA{2}\n"
    "   static GrayScale{3}\n"
    "   static GrayAlpha{4}\n"
    "   foreign format\n"
    "   foreign [index]\n"
    "   foreign [index]=(value)\n"
    "}\n"
    "foreign class Font {\n"
    "   construct load(path, size)\n"
    "}\n"
    ;

    const char* mageInputModule = 
    "import \"mage-utils\" for Vec2\n"
    "class Mouse {\n"
    "   construct new() {}\n"
    "   static LeftButton {1}\n"
    "   static MiddleButton {2}\n"
    "   static RightButton {3}\n"
    "   foreign isPressed(button)\n"
    "   foreign isReleased(button)\n"
    "   foreign isHeld(button)\n"
    "   foreign isUp(button)\n"
    "   foreign x\n"
    "   foreign y\n"
    "   pos {Vec2.new(this.x, this.y)}\n"
    "   foreign dx\n"
    "   foreign dy\n"
    "   dpos {Vec2.new(this.dx, this.dy)}\n"
    "   foreign hscroll\n"
    "   foreign vscroll\n"
    "}\n"
    "class Keyboard{\n"
    "   construct new() {}\n"
    "   static Space{1}\n"
    "   static Apostrophe{2}\n"
    "   static Comma{3}\n"
    "   static Minus{4}\n"
    "   static Period{5}\n"
    "   static Slash{6}\n"
    "   static Zero{7}\n"
    "   static One{8}\n"
    "   static Two{9}\n"
    "   static Three{10}\n"
    "   static Four{11}\n"
    "   static Five{12}\n"
    "   static Six{13}\n"
    "   static Seven{14}\n"
    "   static Eight{15}\n"
    "   static Nine{16}\n"
    "   static Semicolon{17}\n"
    "   static Equal{18}\n"
    "   static A{19}\n"
    "   static B{20}\n"
    "   static C{21}\n"
    "   static D{22}\n"
    "   static E{23}\n"
    "   static F{24}\n"
    "   static G{25}\n"
    "   static H{26}\n"
    "   static I{27}\n"
    "   static J{28}\n"
    "   static K{29}\n" 
    "   static L{30}\n"
    "   static M{31}\n"
    "   static N{32}\n"
    "   static O{33}\n"
    "   static P{34}\n"
    "   static Q{35}\n"
    "   static R{36}\n"
    "   static S{37}\n"
    "   static T{38}\n"
    "   static U{39}\n"
    "   static V{40}\n"
    "   static W{41}\n"
    "   static X{42}\n"
    "   static Y{43}\n"
    "   static Z{44}\n"
    "   static LeftBracket{45}\n"
    "   static Backslash{46}\n"
    "   static RightBracket{47}\n"
    "   static GraveAccent{48}\n"
    "   static World1{49}\n"
    "   static World2{50}\n"
    "   static Escape{51}\n"
    "   static Enter{52}\n"
    "   static Tab{53}\n"
    "   static Backspace{54}\n"
    "   static Insert{55}\n"
    "   static Delete{56}\n"
    "   static Right{57}\n"
    "   static Left{58}\n"
    "   static Down{59}\n"
    "   static Up{60}\n"
    "   static PageUp{61}\n"
    "   static PageDown{62}\n"
    "   static Home{63}\n"
    "   static End{64}\n"
    "   static CapsLock{65}\n"
    "   static ScrollLock{66}\n"
    "   static NumLock{67}\n"
    "   static PrintScreen{68}\n"
    "   static Pause{69}\n"
    "   static F1{70}\n"
    "   static F2{71}\n"
    "   static F3{72}\n"
    "   static F4{73}\n"
    "   static F5{74}\n"
    "   static F6{75}\n"
    "   static F7{76}\n" 
    "   static F8{77}\n"
    "   static F9{78}\n"
    "   static F10{79}\n"
    "   static F11{80}\n"
    "   static F12{81}\n"
    "   static F13{82}\n"
    "   static F14{83}\n" 
    "   static F15{84}\n"
    "   static F16{85}\n"
    "   static F17{86}\n"
    "   static F18{87}\n"
    "   static F19{88}\n"
    "   static F20{89}\n"
    "   static F21{90}\n"
    "   static F22{91}\n"
    "   static F23{92}\n"
    "   static F24{93}\n" 
    "   static F25{94}\n"
    "   static KP0{95}\n"
    "   static KP1{96}\n"
    "   static KP2{97}\n"
    "   static KP3{98}\n"
    "   static KP4{99}\n"
    "   static KP5{100}\n"
    "   static KP6{101}\n"
    "   static KP7{102}\n"
    "   static KP8{103}\n"
    "   static KP9{104}\n"
    "   static KPDecimal{105}\n"
    "   static KPDivide{106}\n"
    "   static KPMultiply{107}\n"
    "   static KPSubtract{108}\n"
    "   static KPAdd{109}\n"
    "   static KPEnter{110}\n"
    "   static KPEqual{111}\n"
    "   static LeftShift{112}\n"
    "   static LeftControl{113}\n"
    "   static LeftAlt{114}\n"
    "   static LeftSuper{115}\n"
    "   static RightShift{116}\n"
    "   static RightControl{117}\n"
    "   static RightAlt{118}\n"
    "   static RightSuper{119}\n"
    "   static Menu{120}\n"
    "   foreign isPressed(key)\n"
    "   foreign isReleased(key)\n"
    "   foreign isHeld(key)\n"
    "   foreign isUp(key)\n"
    "   foreign getChar()\n"
    "}\n"
    ;

    const char* mageGraphicsModule = 
    "import \"mage-res\" for Image\n"
    "foreign class Texture {\n"
    "   construct loadFromImage(image) {}\n"
    "   static load(path) {\n"
    "       return Texture.loadFromImage(Image.new)\n"
    "   }\n"
    "   foreign width\n"
    "   foreign height\n"
    "}\n"
    ;

    const char* mageAudioModule = 
    "class AudioContext {\n"
    "   construct new() {}\n"
    "   foreign play(path, isLooping)\n"
    "   play(path) { play(path, true) }\n" 
    "}\n"
    ;

    const char* mageAppModule = 
    "import \"mage-utils\" for Vec2, Color\n"
    "import \"mage-window\" for Window\n"
    "import \"mage-timer\" for InternalClock\n"
    "import \"mage-camera\" for Camera\n"
    "import \"mage-input\" for Mouse, Keyboard\n"
    "import \"mage-audio\" for AudioContext\n"
    "class AppConfig {\n"
    "   construct new() {}\n"
    "   foreign width=(value)\n"
    "   foreign height=(value)\n"
    "   foreign title=(value)\n"
    "   foreign background_color=(value)\n"
    "   foreign resizable=(value)\n"
    "   foreign fullscreen=(value)\n"
    "   foreign decorated=(value)\n"
    "   foreign maximized=(value)\n"
    "   foreign vsync=(value)\n"
    "   foreign transparent=(value)\n"
    "   foreign focused=(value)\n"
    "   foreign halt_while_hidden=(value)\n"
    "   foreign fps_cap=(value)\n"
    "   foreign opacity=(value)\n"
    "   foreign min_size=(value)\n"
    "   foreign max_size=(value)\n"
    "}\n"
    "class GameContext {\n"
    "   construct new() {\n"
    "       _window = Window.new()\n"
    "       _timer = InternalClock.new()\n"
    "       _camera = Camera.new()\n"
    "       _mouse = Mouse.new()\n"
    "       _keyboard = Keyboard.new()\n"
    "       _audio = AudioContext.new()\n"
    "   }\n"
    "   window {_window}\n"
    "   timer {_timer}\n"
    "   camera {_camera}\n"
    "   mouse {_mouse}\n"
    "   keyboard {_keyboard}\n"
    "   audio {_audio}\n"
    "}\n"
    "class RenderContext {\n"
    "   construct new() {}\n"
    "}\n"
    ;
    

    // === MAGE FUNCTION DEFINITIONS
    // == AppConfig
    void appConfigSetWindowWidth(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->width = GET_INT(1);
    }

    void appConfigSetWindowHeight(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->height = GET_INT(1);
    }

    void appConfigSetWindowTitle(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->title = GET_STR(1);
    }

    void appConfigSetWindowResizable(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->resizable = GET_BOOL(1);
    }

    void appConfigSetWindowFullscreen(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->fullscreen = GET_BOOL(1);
    }

    void appConfigSetWindowDecorated(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->decorated = GET_BOOL(1);
    }

    void appConfigSetWindowMaximized(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->maximized = GET_BOOL(1);
    }

    void appConfigSetWindowVSync(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->vsync = GET_BOOL(1);
    }

    void appConfigSetWindowTransparent(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->transparent = GET_BOOL(1);
    }

    void appConfigSetWindowFocused(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->focused = GET_BOOL(1);
    }

    void appConfigSetWindowHaltWhileHidden(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->halt_while_hidden = GET_BOOL(1);
    }

    void appConfigSetWindowFPSCap(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->fps_cap = GET_INT(1);
    }

    void appConfigSetWindowOpacity(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->resizable = GET_FLOAT(1);
    }

    void appConfigSetWindowMinSize(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->min_size = *(arcana::Vector2*)GET_FOREIGN(1);
    }

    void appConfigSetWindowMaxSize(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->max_size = *(arcana::Vector2*)GET_FOREIGN(1);
    }

    void appConfigSetWindowBackgroundColor(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->background_color = *(arcana::Color*)GET_FOREIGN(1);
    }
    //== Vector2
    void vec2Constructor(WrenVM* vm) {
        arcana::Vector2* vec = SET_FOREIGN(arcana::Vector2);
        new (vec) arcana::Vector2(GET_FLOAT(1), GET_FLOAT(2));
    }

    void vec2GetX(WrenVM* vm) {
        arcana::Vector2* vec = (arcana::Vector2*)GET_FOREIGN(0);
        SET_NUM(vec->x, 0);
    }

    void vec2GetY(WrenVM* vm) {
        arcana::Vector2* vec = (arcana::Vector2*)GET_FOREIGN(0);
        SET_NUM(vec->y, 0);
    }

    void vec2SetX(WrenVM* vm) {
        arcana::Vector2* vec = (arcana::Vector2*)GET_FOREIGN(0);
        vec->x = GET_FLOAT(1);
    }

    void vec2SetY(WrenVM* vm) {
        arcana::Vector2* vec = (arcana::Vector2*)GET_FOREIGN(0);
        vec->y = GET_FLOAT(1);
    }
    //== Vector3
    void vec3Constructor(WrenVM* vm) {
        arcana::Vector3* vec = SET_FOREIGN(arcana::Vector3);
        new (vec) arcana::Vector3(GET_FLOAT(1), GET_FLOAT(2), GET_FLOAT(3));
    }

    void vec3GetX(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        SET_NUM(vec->x, 0);
    }

    void vec3GetY(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        SET_NUM(vec->y, 0);
    }

    void vec3GetZ(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        SET_NUM(vec->z, 0);
    }

    void vec3SetX(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        vec->x = GET_FLOAT(1);
    }

    void vec3SetY(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        vec->y = GET_FLOAT(1);
    }

    void vec3SetZ(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        vec->z = GET_FLOAT(1);
    }
    //== Vector4
    void vec4Constructor(WrenVM* vm) {
        arcana::Vector4* vec = SET_FOREIGN(arcana::Vector4);
        new (vec) arcana::Vector4(GET_FLOAT(1), GET_FLOAT(2), GET_FLOAT(3), GET_FLOAT(4));
    }

    void vec4GetX(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        SET_NUM(vec->x, 0);
    }

    void vec4GetY(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        SET_NUM(vec->y, 0);
    }

    void vec4GetZ(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        SET_NUM(vec->z, 0);
    }

    void vec4GetW(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        SET_NUM(vec->w, 0);
    }

    void vec4SetX(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        vec->x = GET_FLOAT(1);
    }

    void vec4SetY(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        vec->y = GET_FLOAT(1);
    }

    void vec4SetZ(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        vec->z = GET_FLOAT(1);
    }

    void vec4SetW(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        vec->w = GET_FLOAT(1);
    }
    //== Color
    void colorConstructor(WrenVM* vm) {
        arcana::Color* color = SET_FOREIGN(arcana::Color);
        new (color) arcana::Color(GET_INT(1), GET_INT(2), GET_INT(3), GET_INT(4));
    }

    void colorGetR(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        SET_NUM(color->r, 0);
    }

    void colorGetG(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        SET_NUM(color->g, 0);
    }

    void colorGetB(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        SET_NUM(color->b, 0);
    }

    void colorGetA(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        SET_NUM(color->a, 0);
    }

    void colorSetR(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        int num = GET_INT(1);
        if (num > 255 && num < 0) {
            ERROR("Error: Color value set is not within bounds!")
        }
        else {
            color->r = GET_INT(1);
        }
    }

    void colorSetG(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        int num = GET_INT(1);
        if (num > 255 && num < 0) {
            ERROR("Error: Color value set is not within bounds!")
        }
        else {
            color->g = GET_INT(1);
        }
    }

    void colorSetB(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        int num = GET_INT(1);
        if (num > 255 && num < 0) {
            ERROR("Error: Color value set is not within bounds!")
        }
        else {
            color->b = GET_INT(1);
        }
    }

    void colorSetA(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        int num = GET_INT(1);
        if (num > 255 && num < 0) {
            ERROR("Error: Color value set is not within bounds!")
        }
        else {
            color->a = GET_INT(1);
        }
    }

    //== Random
    void randomGenerate(WrenVM* vm) {
        SET_NUM(arcana::random::generate(),0);
    } 
    void randomGenerateNum(WrenVM* vm) {
        SET_NUM(arcana::random::generateNum(GET_INT(1), GET_INT(2)),0);
    }
    void randomSetSeed(WrenVM* vm) {
        arcana::random::setSeed(GET_INT(1));
    } 

    //== Window
    void windowClose(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->window.close();
    }

    void windowRestore(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->window.restoreWindow();
    }

    void windowMinimize(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->window.minimizeWindow();
    }

    void windowMaximize(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->window.maximizeWindow();
    }

    void windowIsMaximized(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_BOOL(uData->game_ctx->window.isMaximized(), 0);
    }

    void windowIsMinimized(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_BOOL(uData->game_ctx->window.isMinimized(), 0);
    }

    void windowWasResized(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_BOOL(uData->game_ctx->window.wasResized(), 0);
    }

    void windowWasMoved(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_BOOL(uData->game_ctx->window.wasMoved(), 0);
    }

    void windowGetPosX(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->window.getPos().x, 0);
    }

    void windowGetPosY(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->window.getPos().y, 0);
    }

    void windowGetWidth(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->window.getWindowSize().x, 0);
    }

    void windowGetHeight(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->window.getWindowSize().y, 0);
    }

    void windowSetPos(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->window.setWindowPos(*(arcana::Vector2*)GET_FOREIGN(1));
    }

    void windowSetTitle(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->window.updateTitle(GET_STR(1));
    }
    //== Timer
    void timerConstructor(WrenVM* vm) {
        arcana::Timer* timer = SET_FOREIGN(arcana::Timer);
        new (timer) arcana::Timer();
    }
    
    void timerReset(WrenVM* vm) {
        arcana::Timer* timer = (arcana::Timer*)GET_FOREIGN(0);
        timer->reset();
    }

    void timerGetElapsed(WrenVM* vm) {
        arcana::Timer* timer = (arcana::Timer*)GET_FOREIGN(0);
        SET_NUM(timer->getElapsed(), 0);
    }

    void timerGetElapsedMillis(WrenVM* vm) {
        arcana::Timer* timer = (arcana::Timer*)GET_FOREIGN(0);
        SET_NUM(timer->getElapsedMillis(), 0);
    }
    //== Internal clock
    void ctxTimerGetDelta(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->timer.dt(), 0);
    }

    void ctxTimerGetFPS(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->timer.fps(), 0);
    }

    //== Camera
    void cameraGetXOffset(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->camera.get()->offset.x, 0);
    }

    void cameraGetYOffset(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->camera.get()->offset.y, 0);
    }

    void cameraGetZoom(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->camera.get()->zoom, 0);
    }

    void cameraGetRotation(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->camera.get()->rotation, 0);
    }

    void cameraSetOffset(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->camera.get()->offset = *(arcana::Vector2*)GET_FOREIGN(1);
    }

    void cameraSetZoom(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->camera.get()->zoom = GET_FLOAT(1);
    }

    void cameraSetRotation(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->camera.get()->zoom = GET_FLOAT(1);
    }

    //== Filesystem
    void filesystemSetCWD(WrenVM* vm) {
        arcana::filesystem::setDir(GET_STR(1));
    }

    void filesystemCheckDirExists(WrenVM* vm) {
        SET_BOOL(arcana::filesystem::dirExists(GET_STR(1)), 0);
    }

    void filesystemCheckFileExists(WrenVM* vm) {
        SET_BOOL(arcana::filesystem::fileExists(GET_STR(1)), 0);
    }

    void filesystemLoadFile(WrenVM* vm) {
        size_t fsize;
        char* filedata = arcana::filesystem::loadFileText(GET_STR(1), fsize);
        SET_STR(filedata, 0);
        arcana::filesystem::unloadFileText(filedata);
    }

    void filesystemSaveFile(WrenVM* vm) {
        arcana::filesystem::saveFileText(GET_STR(1), (char*)GET_STR(2));
    }

    //== Mouse
    void mouseIsPressed(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        arcana::MouseButton button = (arcana::MouseButton)GET_INT(1);
        SET_BOOL(uData->game_ctx->mouse.isPressed(button), 0);
    }

    void mouseIsReleased(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        arcana::MouseButton button = (arcana::MouseButton)GET_INT(1);
        SET_BOOL(uData->game_ctx->mouse.isReleased(button), 0);
    }

    void mouseIsHeld(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        arcana::MouseButton button = (arcana::MouseButton)GET_INT(1);
        SET_BOOL(uData->game_ctx->mouse.isHeld(button), 0);
    }

    void mouseIsUp(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        arcana::MouseButton button = (arcana::MouseButton)GET_INT(1);
        SET_BOOL(uData->game_ctx->mouse.isUp(button), 0);
    }

    void mouseGetXPos(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->mouse.getPos().x, 0);
    }

    void mouseGetYPos(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->mouse.getPos().y, 0);
    }

    void mouseGetDeltaX(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->mouse.getDeltaPos().x, 0);
    }

    void mouseGetDeltaY(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->mouse.getDeltaPos().y, 0);
    }

    void mouseGetHScroll(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->mouse.getScroll().x, 0);
    }

    void mouseGetVScroll(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        SET_NUM(uData->game_ctx->mouse.getScroll().y, 0);
    }
    
    //== Keyboard
    void keyboardIsPressed(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        arcana::Key key = (arcana::Key)GET_INT(1);
        SET_BOOL(uData->game_ctx->keyboard.isPressed(key), 0);
    }

    void keyboardIsReleased(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        arcana::Key key = (arcana::Key)GET_INT(1);
        SET_BOOL(uData->game_ctx->keyboard.isReleased(key), 0);
    }

    void keyboardIsHeld(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        arcana::Key key = (arcana::Key)GET_INT(1);
        SET_BOOL(uData->game_ctx->keyboard.isHeld(key), 0);
    }

    void keyboardIsUp(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        arcana::Key key = (arcana::Key)GET_INT(1);
        SET_BOOL(uData->game_ctx->keyboard.isUp(key), 0);
    }

    void keyboardGetChar(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        unsigned char character = uData->game_ctx->keyboard.getCharPressed();
        if (character != 0) {
            std::string strchar;
            strchar += character;
            SET_STR(strchar.c_str(), 0);
        }
        else {
            SET_NUM(character, 0);
        }
    }

    //== Audio 
    void audioContextPlay(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->game_ctx->audio.play(GET_STR(1), GET_BOOL(2));
    }

    //== Image
    void imageConstructor(WrenVM* vm) {
        arcana::Image* image = SET_FOREIGN(arcana::Image);
        new (image) arcana::Image(GET_STR(1));
    }

    void imageGetWidth(WrenVM* vm) {
        arcana::Image* image = (arcana::Image*)GET_FOREIGN(0);
        SET_NUM(image->width, 0);
    }

    void imageGetFormat(WrenVM* vm) {
        arcana::Image* image = (arcana::Image*)GET_FOREIGN(0);
        SET_NUM(image->format, 0);
    } 

    void imageGetPixelData(WrenVM* vm) {
        arcana::Image* image = (arcana::Image*)GET_FOREIGN(0);
        int index = GET_INT(1);
        // Convert format to int
        int pxSize;
        switch (image->format) {
            case arcana::GRAYSCALE: pxSize = 1;
            case arcana::GRAY_ALPHA: pxSize = 2;
            case arcana::RGB: pxSize = 3;
            case arcana::RGBA: pxSize = 4;
            default: pxSize = 1;
        }
        if (index >= image->width * image->height * pxSize || index < 0) {
            ERROR("Error: Image index out of range!")
            SET_NUM(0, 0);
        }
        else {
            SET_NUM(image->data[index], 0);
        }
        SET_NUM(image->format, 0);
    } 

    void imageSetPixelData(WrenVM* vm) {
        arcana::Image* image = (arcana::Image*)GET_FOREIGN(0);
        int index = GET_INT(1);
        int value = GET_INT(2);
        // Convert format to int
        int pxSize;
        switch (image->format) {
            case arcana::GRAYSCALE: pxSize = 1;
            case arcana::GRAY_ALPHA: pxSize = 2;
            case arcana::RGB: pxSize = 3;
            case arcana::RGBA: pxSize = 4;
            default: pxSize = 1;
        }
        if (index >= image->width * image->height * pxSize || index < 0) {
            ERROR("Error: Image index out of range!")
            SET_NUM(0, 0);
        }
        else {
            if (value < 0 || value > 255) {
                ERROR("Error: Image pixel not set to a valid color value!")
            }
            else {
                image->data[index] = value;
            }
        }
        SET_NUM(image->format, 0);
    } 
    

    void imageGetHeight(WrenVM* vm) {
        arcana::Image* image = (arcana::Image*)GET_FOREIGN(0);
        SET_NUM(image->height, 0);
    }

    void imageDestructor(void* data) {
        ((arcana::Image*)data)->~Image();
    }

    //== Texture 
    void texConstructor(WrenVM* vm) {
        arcana::Texture* tex = SET_FOREIGN(arcana::Texture);
        new (tex) arcana::Texture(*((arcana::Image*)GET_FOREIGN(1)));
    }

    void texGetWidth(WrenVM* vm) {
        arcana::Texture* tex = (arcana::Texture*)GET_FOREIGN(0);
        SET_NUM(tex->width, 0);
    }

    void texGetHeight(WrenVM* vm) {
        arcana::Texture* tex = (arcana::Texture*)GET_FOREIGN(0);
        SET_NUM(tex->height, 0);
    }

    void texDestructor(void* data) {
        ((arcana::Texture*)data)->~Texture();
    }

    //== Shader 


    //== Font
    void fontConstructor(WrenVM* vm) {
        arcana::Font* font = SET_FOREIGN(arcana::Font);
        new (font) arcana::Font(GET_STR(1), GET_INT(2));
    }

    void fontDestructor(void* data) {
        ((arcana::Font*)data)->~Font();
    }

    //== Point
    void pointConstructor(WrenVM* vm) {
        arcana::Point* point = SET_FOREIGN(arcana::Point);
        new (point) arcana::Point({GET_INT(1), GET_INT(2)});
    }

    void pointGetPosX(WrenVM* vm) {
        arcana::Vector2 pos = ((arcana::Point*)GET_FOREIGN(0))->pos;
        SET_NUM(pos.x, 0);
    }

    void pointGetPosY(WrenVM* vm) {
        arcana::Vector2 pos = ((arcana::Point*)GET_FOREIGN(0))->pos;
        SET_NUM(pos.y, 0);
    }

    void pointSetPos(WrenVM* vm) {
        arcana::Point* point = ((arcana::Point*)GET_FOREIGN(0));
        point->pos = *((arcana::Vector2*)GET_FOREIGN(1));
    }

    //== Line
    void lineConstructor(WrenVM* vm) {
        arcana::Line* line = SET_FOREIGN(arcana::Line);
        arcana::Vector2* startPoint = (arcana::Vector2*)GET_FOREIGN(1);
        arcana::Vector2* endPoint = (arcana::Vector2*)GET_FOREIGN(2);
        new (line) arcana::Line(*startPoint, *endPoint);
    }

    void lineGetStartX(WrenVM* vm) {
        arcana::Line* line = (arcana::Line*)GET_FOREIGN(1);
        SET_NUM(line->startPoint.x, 0);
    }

    void lineGetStartY(WrenVM* vm) {
        arcana::Line* line = (arcana::Line*)GET_FOREIGN(1);
        SET_NUM(line->startPoint.y, 0);
    }

    void lineGetEndX(WrenVM* vm) {
        arcana::Line* line = (arcana::Line*)GET_FOREIGN(1);
        SET_NUM(line->endPoint.x, 0);
    }

    void lineGetEndY(WrenVM* vm) {
        arcana::Line* line = (arcana::Line*)GET_FOREIGN(1);
        SET_NUM(line->endPoint.y, 0);
    }

    void lineSetStartPos(WrenVM* vm) {
        arcana::Line* line = ((arcana::Line*)GET_FOREIGN(0));
        line->startPoint = *((arcana::Vector2*)GET_FOREIGN(1));
    }

    void lineSetEndPos(WrenVM* vm) {
        arcana::Line* line = ((arcana::Line*)GET_FOREIGN(0));
        line->endPoint = *((arcana::Vector2*)GET_FOREIGN(1));
    }

    // === END MAGE FUNCTION DEFINITIONS

    // Print function for the Wren VM
    void writeFn(WrenVM* vm, const char* str) {
        std::printf("%s", str);
    }

    // Error reporting function
    void errorFn(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg) {
        switch (errorType) 
        {
            case WREN_ERROR_COMPILE:
            {
                MAGE_ERROR("[{0} line {1}] [Error] {2}", module, line, msg);
            } break;

            case WREN_ERROR_STACK_TRACE:
            {
                MAGE_ERROR("[{0} line {1}] in {2}", module, line, msg);
            } break;

            case WREN_ERROR_RUNTIME:
            {
                MAGE_ERROR("[Runtime Error] {0}", msg);
            } break;
        }
    }

    // Used to get the file source for MAGE modules
    const char* getMageModuleSource(const char* module) {
        if (strcmp(module, "mage-app") == 0) {
            return mageAppModule;
        }
        else if (strcmp(module, "mage-utils") == 0) {
            return mageUtilsModule;
        }
        else if (strcmp(module, "mage-random") == 0) {
            return mageRandomModule;
        }
        else if (strcmp(module, "mage-window") == 0) {
            return mageWindowModule;
        }
        else if (strcmp(module, "mage-timer") == 0) {
            return mageTimerModule;
        }
        else if (strcmp(module, "mage-camera") == 0) {
            return mageCameraModule;
        }
        else if (strcmp(module, "mage-res") == 0) {
            return mageResModule;
        }
        else if (strcmp(module, "mage-input") == 0) {
            return mageInputModule;
        }
        else if (strcmp(module, "mage-geom") == 0) {
            return mageGeometryModule;
        }
        else if (strcmp(module, "mage-gfx") == 0) {
            return mageGraphicsModule;
        }
        else if (strcmp(module, "mage-audio") == 0) {
            return mageAudioModule;
        }
        else {
            return "";
        }
    }

    // Get the module source
    const char* getSourceForModule(WrenVM* vm, const char* name) {
        // First check if the module is part of the mage modules
        const char* modSource = getMageModuleSource(name);
        if (strcmp(modSource, "") != 0) {
            return modSource;
        }
        else {
            UserData* data = (UserData*)GET_USER_DATA()
            std::string path = data->projectDir;
            path += name;
            path += ".wren";
            size_t fsize;
            return arcana::filesystem::loadFileText(path, fsize);
        }
    }
    
    // Wren function for loading files
    WrenLoadModuleResult loadModuleFn(WrenVM* vm, const char* name) {
        WrenLoadModuleResult result = {0};
            result.source = getSourceForModule(vm, name);
        return result;
    }

    // Used to bind foreign functions
    WrenForeignMethodFn bindForeignFn(WrenVM* vm, const char* module, const char* className,
                                bool isStatic, const char* signature) 
    {
        UserData* uData = (UserData*)GET_USER_DATA();
        WrenLibrary* lib = uData->lib;
        return lib->searchFn(module, className, isStatic, signature);
    }

    // Used to bind foreign classes
    WrenForeignClassMethods bindForeignClass(WrenVM* vm, const char* module, const char* className) 
    {
        UserData* uData = (UserData*)GET_USER_DATA();
        WrenLibrary* lib = uData->lib;
        WrenForeignClassMethods fClass;
        lib->searchFClass(module, className, &fClass);
        return fClass;
    }

    Frontend::Frontend() {

    }

    void Frontend::start(const std::string& fpath) {
        // Now load up every part of the MAGE engine
        // First the VM
        wrenInitConfiguration(&wrenConfig);
            wrenConfig.writeFn = writeFn;
            wrenConfig.errorFn = errorFn;  
            wrenConfig.loadModuleFn = loadModuleFn;
            wrenConfig.bindForeignMethodFn = bindForeignFn;
            wrenConfig.bindForeignClassFn = bindForeignClass;
        vm = wrenNewVM(&wrenConfig);
        MAGE_INFO("Frontend: Loaded the Wren VM!");
        // Now declare the MAGE library 
        declMageLib();
        // Set user data
        uData.projectDir = fpath;
        uData.lib = &mageLib;
        SET_USER_DATA(&uData);
        // Now load the main class
        loadMain();
    }

    void Frontend::loadMain() {
        std::string source = getSourceForModule(vm, "main");
        WrenInterpretResult result = wrenInterpret(vm, "main", source.c_str()); 
        // Then handle the results of the interpretation
        switch (result) {
        case WREN_RESULT_COMPILE_ERROR:
        { MAGE_ERROR("Wren: Encountered a compile error while running the project!"); } break;
        case WREN_RESULT_RUNTIME_ERROR:
        { MAGE_ERROR("Wren: Encountered a runtime error while running the project!"); } break;
        case WREN_RESULT_SUCCESS:
        { MAGE_INFO("Wren: Succesfully compiled main!"); } break;
        }
        // Now load the main class and function handles
        // Load the main class
        ENSURE_SLOTS(1);
        GET_VARIABLE("main", "Main", 0);
        WrenHandle* constructor = MAKE_HANDLE("new()");
        CALL_FUNC(constructor);
        RELEASE_HANDLE(constructor);
        app.mainInstance = GET_HANDLE(0);
        // Now time to get all attached functions
        app.configFunc = MAKE_HANDLE("config(_)");
        app.initFunc = MAKE_HANDLE("init(_)");
        app.updateFunc = MAKE_HANDLE("update(_)");
        app.renderFunc = MAKE_HANDLE("render(_)");
        app.finishFunc = MAKE_HANDLE("finish()");

        // And also load the context and config classes
        ENSURE_SLOTS(1);
        GET_VARIABLE("mage-app", "AppConfig", 0);
        constructor = MAKE_HANDLE("new()");
        CALL_FUNC(constructor);
        RELEASE_HANDLE(constructor);
        app.configInstance = GET_HANDLE(0);

        ENSURE_SLOTS(1);
        GET_VARIABLE("mage-app", "GameContext", 0);
        constructor = MAKE_HANDLE("new()");
        CALL_FUNC(constructor);
        RELEASE_HANDLE(constructor);
        app.gameCtxInstance = GET_HANDLE(0);

        ENSURE_SLOTS(1);
        GET_VARIABLE("mage-app", "RenderContext", 0);
        constructor = MAKE_HANDLE("new()");
        CALL_FUNC(constructor);
        RELEASE_HANDLE(constructor);
        app.renderCtxInstance = GET_HANDLE(0);
    }

    void Frontend::declMageLib() {
        mageLib
        .declModule("mage-utils")
            .declClass("Vec2")
                .declForeignAlloc(vec2Constructor)
                .declForeignFn("x", false, vec2GetX)
                .declForeignFn("y", false, vec2GetY)
                .declForeignFn("x=(_)", false, vec2SetX)
                .declForeignFn("y=(_)", false, vec2SetY)
            .declClass("Vec3")
                .declForeignAlloc(vec3Constructor)
                .declForeignFn("x", false, vec3GetX)
                .declForeignFn("y", false, vec3GetY)
                .declForeignFn("z", false, vec3GetZ)
                .declForeignFn("x=(_)", false, vec3SetX)
                .declForeignFn("y=(_)", false, vec3SetY)
                .declForeignFn("z=(_)", false, vec3SetZ)
            .declClass("Vec4")
                .declForeignAlloc(vec4Constructor)
                .declForeignFn("x", false, vec4GetX)
                .declForeignFn("y", false, vec4GetY)
                .declForeignFn("z", false, vec4GetZ)
                .declForeignFn("w", false, vec4GetW)
                .declForeignFn("x=(_)", false, vec4SetX)
                .declForeignFn("y=(_)", false, vec4SetY)
                .declForeignFn("z=(_)", false, vec4SetZ)
                .declForeignFn("w=(_)", false, vec4SetW)
            .declClass("Color")
                .declForeignAlloc(colorConstructor)
                .declForeignFn("r", false, colorGetR)
                .declForeignFn("g", false, colorGetG)
                .declForeignFn("b", false, colorGetB)
                .declForeignFn("a", false, colorGetA)
                .declForeignFn("r=(_)", false, colorSetR)
                .declForeignFn("g=(_)", false, colorSetG)
                .declForeignFn("b=(_)", false, colorSetB)
                .declForeignFn("a=(_)", false, colorSetA)
        .declModule("mage-random")
            .declClass("Random")
                .declForeignFn("generate()", true, randomGenerate)
                .declForeignFn("generate(_,_)", true, randomGenerateNum)
                .declForeignFn("seed=(_)", true, randomSetSeed)
        .declModule("mage-res")
            .declClass("Filesystem")
                .declForeignFn("cwd=(_)", true, filesystemSetCWD)
                .declForeignFn("dirExists(_)", true, filesystemCheckDirExists)
                .declForeignFn("fileExists(_)", true, filesystemCheckFileExists)
                .declForeignFn("load(_)", true, filesystemLoadFile)
                .declForeignFn("save(_,_)", true, filesystemSaveFile)
            .declClass("Image")
                .declForeignAlloc(imageConstructor)
                .declForeignFn("width", false, imageGetWidth)
                .declForeignFn("height", false, imageGetHeight)
                .declForeignFn("format", false, imageGetFormat)
                .declForeignFn("[_]", false, imageGetPixelData)
                .declForeignFn("[_]=(_)", false, imageSetPixelData)
                .declForeignFinalise(imageDestructor)
            .declClass("Font")
                .declForeignAlloc(fontConstructor)
                .declForeignFinalise(fontDestructor)
        .declModule("mage-window")
            .declClass("Window")
                .declForeignFn("close()", false, windowClose)
                .declForeignFn("restore()", false, windowRestore)
                .declForeignFn("minimize()", false, windowMinimize)
                .declForeignFn("maximize()", false, windowMaximize)
                .declForeignFn("wasResized", false, windowWasResized)
                .declForeignFn("wasMoved", false, windowWasMoved)
                .declForeignFn("isMinimized", false, windowIsMinimized)
                .declForeignFn("isMaximized", false, windowIsMaximized)
                .declForeignFn("x", false, windowGetPosX)
                .declForeignFn("y", false, windowGetPosY)
                .declForeignFn("width", false, windowGetWidth)
                .declForeignFn("height", false, windowGetHeight)
                .declForeignFn("pos=(_)", false, windowSetPos)
                .declForeignFn("title=(_)", false, windowSetTitle)
        .declModule("mage-timer")
            .declClass("Timer")
                .declForeignAlloc(timerConstructor)
                .declForeignFn("reset()", false, timerReset)
                .declForeignFn("elapsed", false, timerGetElapsed)
                .declForeignFn("elapsedMillis", false, timerGetElapsedMillis)
            .declClass("InternalClock")
                .declForeignFn("dt", false, ctxTimerGetDelta)
                .declForeignFn("fps", false, ctxTimerGetFPS)
        .declModule("mage-camera")
            .declClass("Camera")
                .declForeignFn("xoffset", false, cameraGetXOffset)
                .declForeignFn("yoffset", false, cameraGetYOffset)
                .declForeignFn("zoom", false, cameraGetZoom)
                .declForeignFn("rotation", false, cameraGetRotation)
                .declForeignFn("offset=(_)", false, cameraSetOffset)
                .declForeignFn("zoom=(_)", false, cameraSetZoom)
                .declForeignFn("rotation=(_)", false, cameraSetRotation)
        .declModule("mage-input")
            .declClass("Mouse")
                .declForeignFn("isPressed(_)", false, mouseIsPressed)
                .declForeignFn("isReleased(_)", false, mouseIsReleased)
                .declForeignFn("isHeld(_)", false, mouseIsHeld)
                .declForeignFn("isUp(_)", false, mouseIsUp)
                .declForeignFn("x", false, mouseGetXPos)
                .declForeignFn("y", false, mouseGetYPos)
                .declForeignFn("dx", false, mouseGetDeltaX)
                .declForeignFn("dy", false, mouseGetDeltaY)
                .declForeignFn("hscroll", false, mouseGetHScroll)
                .declForeignFn("vscroll", false, mouseGetVScroll)
            .declClass("Keyboard")
                .declForeignFn("isPressed(_)", false, keyboardIsPressed)
                .declForeignFn("isReleased(_)", false, keyboardIsReleased)
                .declForeignFn("isHeld(_)", false, keyboardIsHeld)
                .declForeignFn("isUp(_)", false, keyboardIsUp)
                .declForeignFn("getChar()", false, keyboardGetChar)
        .declModule("mage-geom")
            .declClass("Point")
                .declForeignAlloc(pointConstructor)
                .declForeignFn("x", false, pointGetPosX)
                .declForeignFn("y", false, pointGetPosY)
                .declForeignFn("pos=(_)", false, pointSetPos)
            .declClass("Line")
                .declForeignAlloc(lineConstructor)
                .declForeignFn("startX", false, lineGetStartX)
                .declForeignFn("startY", false, lineGetStartY)
                .declForeignFn("endX", false, lineGetEndX)
                .declForeignFn("endY", false, lineGetEndY)
                .declForeignFn("startPos=(_)", false, lineSetStartPos)
                .declForeignFn("endPos=(_)", false, lineSetEndPos)
            .declClass("Triangle") // TODO
            .declClass("Quadrilateral") // TODO
            .declClass("Rectangle") // TODO
            .declClass("Circle") // TODO
        .declModule("mage-gfx")
            .declClass("Shader") // TODO
            .declClass("Texture")
                .declForeignAlloc(texConstructor)
                .declForeignFn("width", false, texGetWidth)
                .declForeignFn("height", false, texGetHeight)
                .declForeignFinalise(texDestructor)
        .declModule("mage-audio")
            .declClass("AudioContext")
                .declForeignFn("play(_,_)", false, audioContextPlay)
        .declModule("mage-app")
            .declClass("AppConfig")
                .declForeignFn("width=(_)", false, appConfigSetWindowWidth)
                .declForeignFn("height=(_)", false, appConfigSetWindowHeight)
                .declForeignFn("title=(_)", false, appConfigSetWindowTitle)
                .declForeignFn("background_color=(_)", false, appConfigSetWindowBackgroundColor)
                .declForeignFn("resizable=(_)", false, appConfigSetWindowResizable)
                .declForeignFn("fullscreen=(_)", false, appConfigSetWindowFullscreen)
                .declForeignFn("decorated=(_)", false, appConfigSetWindowDecorated)
                .declForeignFn("maximized=(_)", false, appConfigSetWindowMaximized)
                .declForeignFn("vsync=(_)", false, appConfigSetWindowVSync)
                .declForeignFn("transparent=(_)", false, appConfigSetWindowTransparent)
                .declForeignFn("focused=(_)", false, appConfigSetWindowFocused)
                .declForeignFn("halt_while_hidden=(_)", false, appConfigSetWindowHaltWhileHidden)
                .declForeignFn("fps_cap=(_)", false, appConfigSetWindowFPSCap)
                .declForeignFn("opacity=(_)", false, appConfigSetWindowOpacity)
                .declForeignFn("min_size=(_)", false, appConfigSetWindowMinSize)
                .declForeignFn("max_size=(_)", false, appConfigSetWindowMaxSize)
        ;
        MAGE_INFO("Wren: Declared the MAGE library!");
    }

    void Frontend::releaseFunctionHandles() {
        RELEASE_HANDLE(app.mainInstance);
        RELEASE_HANDLE(app.configFunc);
        RELEASE_HANDLE(app.initFunc);
        RELEASE_HANDLE(app.updateFunc);
        RELEASE_HANDLE(app.renderFunc);
        RELEASE_HANDLE(app.finishFunc);
        RELEASE_HANDLE(app.configInstance);
        RELEASE_HANDLE(app.gameCtxInstance);
        RELEASE_HANDLE(app.renderCtxInstance);
    }

    Frontend::~Frontend() {
        MAGE_INFO("Frontend: Destroying the engine!");
        // Release handles and Wren VM
        releaseFunctionHandles();
        wrenFreeVM(vm);
    }
}