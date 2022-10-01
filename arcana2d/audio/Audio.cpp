#include "audio/Audio.hpp"

namespace arcana {
    AudioContext::AudioContext() {
        engine = createIrrKlangDevice();
    }

    AudioContext::~AudioContext() {
        
    }

    void AudioContext::play(const char* path, bool looped) {
        engine->play2D(path, looped);
    }
}