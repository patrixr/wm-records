//
//  audioManager.hpp
//  wm-label-visuals
//
//  Created by Patrick Rabier on 16/2/17.
//
//

#ifndef audioManager_hpp
#define audioManager_hpp

#define CHANNEL_COUNT 256
#define USE_MIC 1

#include "ofMain.h"
#include "ofxBeat.h"
#include "ofxProcessFFT.h"

class AudioManager {
    
public:
    static AudioManager   *singleton();
    
    void    playFile(const char * file);
    void    update();
    float*  getChannels();
    float   getMax();
    float   getAverage();
    void    setSmoothFactor(float f);
    
    bool    onBeat;
    
private:
    AudioManager();
    static AudioManager *instance;
    
    #if USE_MIC == 1
        ProcessFFT fft;
    #else
        ofSoundPlayer   player;
    #endif
    
    ofxBeat         beat;
    float*          fftSmooth;
    bool            isPlaying;
    float           smoothFactor;
    
};

#endif /* audioManager_hpp */
