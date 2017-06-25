//
//  Kinect.hpp
//  wm-records
//
//  Created by Patrick Rabier on 18/3/2017.
//
//

#ifndef Kinect_hpp
#define Kinect_hpp

#include "ofMain.h"
#include "../IScene.h"
#include "ofxOpenCv.h"
#include "ofxFboBlur.h"
#include "ofxKinect.h"
#include "../../audio/AudioManager.h"
#include "../../particles/ParticleEmitter.h"

class KinectScene : public IScene {
    
public:
    KinectScene();
    
    
    virtual void draw();
    virtual void update();
    virtual void setup();
    virtual void animateIn();
    virtual void animateOut();
    virtual void keyPressed(int key);
    
    void drawPointCloud();
    
private:
    
    ofxKinect kinect;
    ofLight    spot;
    ofMaterial material;
    ParticleEmitter particles;
    ofxFboBlur gpuBlur;
    
    AudioManager    *audioManager;
    
    int nearThreshold;
    int farThreshold;
    
    int angle;
    int frameCount;
    int offset;
    
    // used for viewing the point cloud
    ofEasyCam easyCam;
    ofImage   logo;
    ofImage   bg;
};

#endif /* Kinect_hpp */
