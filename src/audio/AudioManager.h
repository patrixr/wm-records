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

#include "ofMain.h"
#include "ofxBeat.h"

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
    
    ofSoundPlayer   player;
    ofxBeat         beat;
    float*          fftSmooth;
    bool            isPlaying;
    float           smoothFactor;
};

#endif /* audioManager_hpp */
