//
//  verticesPlay.hpp
//  wm-label-visuals
//
//  Created by Patrick Rabier on 18/2/17.
//
//

#ifndef logo_scene_hpp
#define logo_scene_hpp

#include "ofMain.h"
#include "../IScene.h"

class LogoScene : public IScene {
    
public:
    LogoScene();
    
    
    virtual void draw();
    virtual void update();
    virtual void setup();
    virtual void animateIn();
    virtual void animateOut();
    virtual void keyPressed(int key);
    
private:
    ofMesh              mesh;
    ofImage             image;
    ofEasyCam           easyCam;
    vector<ofVec3f>     positions;
    float               averageFrequency;
    
};

#endif
