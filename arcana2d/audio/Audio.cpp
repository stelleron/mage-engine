#define MINIAUDIO_IMPLEMENTATION
#include "audio/Audio.hpp"
#include "utils/Logger.hpp"
#include "res/Filesystem.hpp"

// WAV file loading 
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

namespace arcana {
    AudioData::AudioData() {
        data = nullptr;
        volume = 1.0f;
        pitch = 1.0f;
        state = NoneState;
        isLooping = false;
        this->frameCount = 0;
        framePos = 0;
    }

    AudioData::AudioData(ma_format format, unsigned int channels,unsigned int sampleRate, unsigned int frameCount) {
        create(format, channels, sampleRate, frameCount);
    }

    AudioData::~AudioData() {
        if(data) {
            delete[] data;
        }
    }

    void AudioData::create(ma_format format, unsigned int channels, unsigned int sampleRate, unsigned int frameCount) {
        data = new float[frameCount * channels];
        ma_data_converter_config converterConfig = ma_data_converter_config_init(format, ma_format_f32, channels, 2, sampleRate, 48000);
        converterConfig.allowDynamicSampleRate = true;

        MiniaudioResult result = ma_data_converter_init(&converterConfig, NULL, &converter);
        if (result != MA_SUCCESS)
        {
            LOG("AUDIO: Couldn't convert audio data!");
        }

        volume = 1.0f;
        pitch = 1.0f;
        state = NoneState;
        isLooping = false;
        this->frameCount = frameCount;
        framePos = 0;
    }

    void AudioData::play() {
        state = Playing;
        framePos = 0;
    }

    AudioContext::AudioContext() {
        // Initialise the device
        AudioDeviceConfig config = ma_device_config_init(ma_device_type_playback);
        config.playback.channels = 2;
        config.playback.format = ma_format_f32;
        config.sampleRate = 48000;

        MiniaudioResult result = ma_device_init(NULL, &config, &device);
        if (result != MA_SUCCESS)
        {
            ERROR("Audio: Could not initialize audio device!");
            return;
        }
    }

    AudioContext::~AudioContext() {
        ma_device_uninit(&device);
    }

    void AudioContext::setVolume(float volume) {
        ma_device_set_master_volume(&device, volume);
    }

    void AudioContext::update() {

    }

    Sound::Sound() {
        isInit = false;
    }

    Sound::~Sound() {
        if (isInit) {

        }
    }

    Sound::Sound(const char* path) {
        load(path);
    }
    
    Sound::Sound(unsigned char* data, size_t size, const char* extension) {
        load(data, size, extension);
    }

    void Sound::load(const char* path) {
        size_t fsize;
        unsigned char* data = filesystem::loadFileData(path, fsize);
        std::string extension = filesystem::getFileExtension(path);
        if (extension == "wav" || extension == "mp3")
            load(data, fsize, extension.c_str());
        else 
            ERROR("Audio: Sound file not supported!");
        delete[] data;
    }

    void Sound::load(unsigned char* data, size_t size, const char* extension) {
        // First check extension type
        std::string extBuffer = extension;
        // Load .wav file here
        if (extBuffer == "wav") {
            drwav wave = {0};
            if (!drwav_init_memory(&wave, data, size, NULL)) {
                ERROR("Audio: Could not load .wav file!");
                return;
            }

            // Read frames
            short* frameData = new short[wave.totalPCMFrameCount * wave.channels];
            drwav_read_pcm_frames_s16(&wave, wave.totalPCMFrameCount, frameData);

            // Now time to generate a sound
            unsigned int frameCount = ma_convert_frames(NULL, 0, ma_format_f32, 2, 48000, NULL, wave.totalPCMFrameCount, ma_format_s16, wave.channels, wave.sampleRate);
            buffer.create(ma_format_f32, 2, 48000, frameCount);
            this->frameCount = ma_convert_frames(buffer.data, frameCount, ma_format_f32, 2, 48000, frameData, wave.totalPCMFrameCount, ma_format_s16, wave.channels, wave.sampleRate);
            this->sampleRate = 48000;
            this->channels = 2;
            this->sampleSize = 32;

            // Unload data
            drwav_uninit(&wave);
            delete[] frameData;
        }
    }
}
