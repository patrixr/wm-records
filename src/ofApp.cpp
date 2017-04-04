#include "ofApp.h"
#include "./scenes/scenes.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);
    
    audioManager = AudioManager::singleton();
    scenes = {
        new KinectScene(),
        new LogoScene()
    };
    
    sceneIndex = 0;
    scenes[sceneIndex]->animateIn();
    
    for (int i = 0; i < scenes.size(); ++i) {
        scenes[i]->setup();
    }
    
    audioManager->playFile("sample.mp3");
}

//--------------------------------------------------------------
void ofApp::update(){
    audioManager->update();
    scenes[sceneIndex]->update();
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
}

//--------------------------------------------------------------
void ofApp::draw(){
    scenes[sceneIndex]->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            scenes[sceneIndex]->animateOut();
            sceneIndex = 0;
            scenes[sceneIndex]->animateIn();
            break;
            
        case '2':
            scenes[sceneIndex]->animateOut();
            sceneIndex = 1;
            scenes[sceneIndex]->animateIn();
            break;
    }
    
    scenes[sceneIndex]->keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
