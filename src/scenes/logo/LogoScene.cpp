//
//  testScene.cpp
//  wm-label-visuals
//
//  Created by Patrick Rabier on 16/2/17.
//
//

#include "./LogoScene.h"
#include "../../audio/AudioManager.h"

#define VERTICES_IMAGE_PATH "scenes/verticesPlay/logo.jpg"
#define IMAGE_SCALE_FACTOR 5
#define CONNECTION_DISTANCE 15 // 15
#define INTENSITY_THRESHOLD 150 // 150

LogoScene::LogoScene(){
    averageFrequency = 0;
}

//--------------------------------------------------------------
void LogoScene::setup(){
    AudioManager::singleton()->setSmoothFactor(0.9f);
    image.load(VERTICES_IMAGE_PATH);
    image.resize(ofGetWidth() / IMAGE_SCALE_FACTOR, ofGetHeight() / IMAGE_SCALE_FACTOR);
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableColors();
    mesh.enableIndices();
    easyCam.setPosition(442.983, 0.2341, -544.302);
    easyCam.lookAt(ofVec3f(0,0,0));
    
    // Generate vertices from image
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            
            ofColor c       = image.getColor(x, y);
            float intensity = c.getLightness();
            
            if (intensity >= INTENSITY_THRESHOLD) {
                float saturation    = c.getSaturation();
                float z             = ofMap(saturation, 0, 255, -200, 200);
                ofVec3f pos         = ofVec3f(x * IMAGE_SCALE_FACTOR, y * IMAGE_SCALE_FACTOR, z);
                
                positions.push_back(ofVec3f(x * IMAGE_SCALE_FACTOR, y * IMAGE_SCALE_FACTOR, z));
                mesh.addVertex(pos);
                mesh.addColor(c);
            }
        }
    }
    
    cout << mesh.getNumVertices() << endl;
    
    // Connect vertices with lines
    float connectionDistance    = CONNECTION_DISTANCE;
    int numVerts                = mesh.getNumVertices();
    
    for (int a = 0; a < numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        
        for (int b=a+1; b<numVerts; ++b) {
            ofVec3f vertb  = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            
            if (distance <= connectionDistance) {
                // In OF_PRIMITIVE_LINES, every pair of vertices or indices will be
                // connected to form a line
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
        }
    }
    
    image.clear();
}

//--------------------------------------------------------------
void LogoScene::draw(){
    ofColor edgeColor = ofColor(255 * (averageFrequency * 5));
    ofColor centerColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    //ofBackground(255 * (averageFrequency * 5), 0, 0);
    
    easyCam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    mesh.draw(OF_MESH_FILL);
    ofPopMatrix();
    easyCam.end();;
}

//--------------------------------------------------------------
void LogoScene::update(){
    int numVerts = mesh.getNumVertices();
    float* channels = AudioManager::singleton()->getChannels();
    for (int i = 0; i < numVerts; ++i) {
        ofVec3f vert  = mesh.getVertex(i);
        //ofColor color = mesh.getColor(i);
        
        float frequency = channels[i % CHANNEL_COUNT];
        if (frequency < 0 || frequency > 1) {
            frequency = 0;
        }
        float realZ     = positions[i].z;
        
        vert.z = realZ * frequency;
        //        color.r = 255 * frequency;
        //        color.g = 255 - 255 * frequency;
        //        color.b = 255 - 255 * frequency;
        mesh.setVertex(i, vert);
        //mesh.setColor(i, color);
    }
    
    averageFrequency = 0;
    for (int i = 0; i < CHANNEL_COUNT; ++i) {
        averageFrequency += channels[i];
    }
    averageFrequency /= CHANNEL_COUNT;
}

//--------------------------------------------------------------
void LogoScene::animateIn(){
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void LogoScene::animateOut(){
}

//--------------------------------------------------------------
void LogoScene::keyPressed(int key) {
}
