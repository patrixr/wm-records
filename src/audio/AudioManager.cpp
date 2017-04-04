//
//  audioManager.cpp
//  wm-label-visuals
//
//  Created by Patrick Rabier on 16/2/17.
//
//

#include "AudioManager.h"

// --------------------------------------
//  Singleton
// --------------------------------------

AudioManager*    AudioManager::instance = NULL;

AudioManager *AudioManager::singleton() {
    if (AudioManager::instance == NULL) {
        AudioManager::instance = new AudioManager();
    }
    
    return AudioManager::instance;
}


// --------------------------------------
//  Implementation
// --------------------------------------

AudioManager::AudioManager() {
    fftSmooth = new float[CHANNEL_COUNT];
    memset(fftSmooth, 0, CHANNEL_COUNT);
    isPlaying = false;
    smoothFactor = 0.9f;
    onBeat = false;
#if USE_MIC == 1
    fft.setup();
    fft.setNormalize(true);
    fft.setNumFFTBins(CHANNEL_COUNT);
#endif
    
}

void AudioManager::playFile(const char * file) {
#if USE_MIC != 1
    player.load(file);
    player.setLoop(true);
    player.setVolume(0.2);
    player.play();
    isPlaying = player.isPlaying();
#else
    isPlaying = true;
#endif
}

void AudioManager::update() {
    ofSoundUpdate();
    
    fft.update();
    
    if (!isPlaying) {
        return;
    }
    
#if USE_MIC != 1
    float *values = ofSoundGetSpectrum(CHANNEL_COUNT);
    int count = CHANNEL_COUNT;
    float scale = 1;
#else
    vector<float> values = fft.getSpectrum();
    int count = values.size();
    float scale = 0.2;
#endif
    
    for (int i = 0; i < count; ++i) {
        float val = ofMap(values[i], 0, 1, 0, 1) * scale;
        fftSmooth[i] *= smoothFactor;
        if (fftSmooth[i] < val) {
            if (val > 0 && val < 0.1) {
                fftSmooth[i] = 0.1;
            } else {
                fftSmooth[i] = val;
            }
        }
    }
}

float* AudioManager::getChannels() {
    return fftSmooth;
}


float   AudioManager::getAverage() {
    float total = 0;
    float *channels = getChannels();
    
    if (channels == NULL) {
        return 0;
    }
    
    for (int i = 0; i < CHANNEL_COUNT; ++i) {
        total += channels[i];
    }
    
    return total / CHANNEL_COUNT;
}

float   AudioManager::getMax() {
    float max = 0;
    float *channels = getChannels();
    
    if (channels == NULL) {
        return max;
    }
    
    for (int i = 0; i < CHANNEL_COUNT; ++i) {
        if (channels[i] > max) {
            max = channels[i];
        }
    }
    
    return max;
}

void AudioManager::setSmoothFactor(float f) {
    if (f < 0)
        f = 0;
    if (f > 1)
        f = 1;
    smoothFactor = f;
}
