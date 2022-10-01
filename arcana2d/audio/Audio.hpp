#ifndef ARCANA2D_AUDIO
    #define ARCANA2D_AUDIO
    #include <irrklang/irrKlang.h>
    using namespace irrklang;

    namespace arcana {
        class AudioContext {
            ISoundEngine* engine;
            public:
                AudioContext();
                ~AudioContext();

                void play(const char* path, bool looped = false);
        };
    }
#endif