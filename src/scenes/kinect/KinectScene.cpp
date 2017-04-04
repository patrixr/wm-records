//
//  testScene.cpp
//  wm-label-visuals
//
//  Created by Patrick Rabier on 16/2/17.
//
//

#include "./KinectScene.h"
#include "../../audio/AudioManager.h"

KinectScene::KinectScene(){

}

//--------------------------------------------------------------
void KinectScene::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    audioManager = AudioManager::singleton();
    
    // -----------------------------
    // Kinect config
    // -----------------------------
    
    // enable depth->video image calibration
    kinect.setRegistration(true);
    
    //kinect.init();
    //kinect.init(true);        // shows infrared instead of RGB video image
    kinect.init(false, false);  // disable video image (faster fps)
    
    kinect.open();                      // opens first available kinect
    //kinect.open(1);                   // open a kinect by id, starting with 0 (sorted by serial # lexicographically))
    //kinect.open("A00362A08602047A");	// open a kinect using it's unique serial #
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }

    nearThreshold = 230;
    farThreshold  = 70;
    
    // zero the tilt on startup
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
    frameCount = 0;
    
    // -----------------------------
    // Background config
    // -----------------------------
    
    logo.load("logo.jpg");
    
    // -----------------------------
    // BLur config
    // -----------------------------
    ofFbo::Settings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat = GL_RGBA;
    s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
    s.maxFilter = GL_LINEAR; //GL_NEAREST;
    s.numSamples = 0;
    s.numColorbuffers = 1;
    s.useDepth = false;
    s.useStencil = false;
    
    gpuBlur.setup(s, false);
    
    gpuBlur.blurOffset = 1;
    gpuBlur.blurPasses = 1;
    gpuBlur.numBlurOverlays = 20;
    gpuBlur.blurOverlayGain = 11;
}


//--------------------------------------------------------------
void KinectScene::update(){
    kinect.update();
}

//--------------------------------------------------------------
void KinectScene::animateIn(){
    ofSetFrameRate(40);
}

//--------------------------------------------------------------
void KinectScene::animateOut(){
}

//--------------------------------------------------------------
void KinectScene::draw(){
    ofSetBackgroundColor(0);
    ofSetColor(255, 255, 255);

    easyCam.begin();
    logo.draw(0, 0, -500);
    drawPointCloud();
    easyCam.end();
    
    // draw instructions
    ofSetColor(255, 255, 255);
    stringstream reportStream;
    
    frameCount++;
    if (frameCount > 10000)
        frameCount = 0;
}


//--------------------------------------------------------------
void KinectScene::drawPointCloud(){
    int w       = 640;
    int h       = 480;
    float fps   = ofGetFrameRate();
    
    glEnable(GL_DEPTH_TEST);
    ofPushMatrix();
    
    // the projected points are 'upside down' and 'backwards'
    ofScale(1, -1, -1);
    ofTranslate(0, 0, -1000); // center the points a bit

    float *channels = audioManager->getChannels();
    
    int step = fps < 30 ? 4 : 3;
    int i    = 0;
    for(int y = 0; y < h; y += step) {
        for(int x = 0; x < w; x += step) {
            
            if(kinect.getDistanceAt(x, y) > 0) {
                ofVec3f vect = kinect.getWorldCoordinateAt(x, y);
                
                if (vect.z > 2000) {
                    continue;
                }
                
                float val = channels[((y + frameCount) * x) % CHANNEL_COUNT];

                ofColor color = ofColor(130 + val * 125);
                ofSetColor(color);
                
                if (fps > 35)
                    ofDrawSphere(vect.x, vect.y, vect.z, 0.2 + val * ofRandomf() * 20);
                else
                    ofDrawBox(vect.x, vect.y, vect.z, 0.2 + val * ofRandomf() * 20);

                i++;
            }
        }
    }
    
    ofSetColor(150, 150, 150);
    ofPopMatrix();
    
    glDisable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void KinectScene::keyPressed(int key) {
    switch (key) {
        case 'c':
            kinect.setCameraTiltAngle(0); // zero the tilt
            kinect.close();
            break;
            
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
    }
}

