#ifndef ARCANA2D_AUDIO
    #define ARCANA2D_AUDIO
    #include "miniaudio.h"

    namespace arcana {
        // Typedef Miniaudio structs
        typedef ma_device AudioDevice;
        typedef ma_device_config AudioDeviceConfig;
        typedef ma_result MiniaudioResult;
        typedef ma_data_converter AudioConverter;

        // Enum for audio state
        enum AudioState {
            NoneState,
            Playing,
            Paused
        };

        // Used to create a buffer for audio data
        struct AudioData {
            float* data;
            AudioConverter converter;

            float volume;
            float pitch;
            
            AudioState state;
            bool isLooping;
            unsigned int frameCount;
            unsigned int framePos;
            
            // Constructor/destructor
            AudioData();
            AudioData(ma_format format, unsigned int channels,unsigned int sampleRate, unsigned int frameCount);
            ~AudioData();

            // Create a buffer
            void create(ma_format format, unsigned int channels,unsigned int sampleRate, unsigned int frameCount);
            // Play the buffer
            void play();
        };

        // Used to create an audio context that plays sounds and music
        class AudioContext {
            private:
                AudioDevice device;
            public:
                // Constructor
                AudioContext();
                // Destructor
                ~AudioContext();

                void setVolume(float volume); // Set master volume
                void update(); // Update the audio device
        };
        
        // Used to store a sound
        class Sound {
            private:
                bool isInit;
                AudioData buffer;
                unsigned int frameCount;
                unsigned int sampleSize;
                unsigned int sampleRate;
                unsigned int channels;
            public:
                // Constructor
                Sound();
                Sound(const char* path);
                Sound(unsigned char* data, size_t size, const char* extension);
                // Destructor
                ~Sound();

                // Loading functions
                void load(const char* path);
                void load(unsigned char* data, size_t size, const char* extension);
                bool isLoaded(); // Check if the sound has been loaded

                // Play the sound
                inline void play() {buffer.play();}
        };
    }
#endif