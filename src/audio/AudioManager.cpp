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
}

void AudioManager::playFile(const char * file) {
    player.load(file);
    player.setLoop(true);
    player.setVolume(0.2);
    player.play();
    isPlaying = player.isPlaying();
}

void AudioManager::update() {
    ofSoundUpdate();
    beat.update(ofGetElapsedTimeMillis());
    
    if (!isPlaying) {
        return;
    }
    
    float *values = ofSoundGetSpectrum(CHANNEL_COUNT);
    
    beat.audioReceived(values, CHANNEL_COUNT * sizeof(float), CHANNEL_COUNT);
    
    if (beat.kick() == 1) {
        if (!onBeat) {
            onBeat = true;
            //std::cout << "beat" << std::endl;
        }
    } else if (beat.kick() < 1) {
        if (onBeat) {
            onBeat = false;
            //std::cout << "__" << std::endl;
        }
    }

//    if (beat.snare())
//        std::cout << "snare" << std::endl;
//
//    if (beat.hihat())
//        std::cout << "hihat" << std::endl;

    
    for (int i = 0; i < CHANNEL_COUNT; ++i) {
        float val = values[i];
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
