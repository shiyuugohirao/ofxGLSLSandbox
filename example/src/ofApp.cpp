#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // create new ofxGLSLSandbox instance
    glslSandbox = new ofxGLSLSandbox(ofGetWidth(), ofGetHeight());

    // setup shader width and height
    //glslSandbox->setResolution(800, 480);

    // load fragment shader file
    glslSandbox->loadFile("shader/shader.frag", GL_FRAGMENT_SHADER);
}

void ofApp::update(){
    
}

void ofApp::draw(){
    // draw shader
    glslSandbox->draw();

    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate(), 4), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // set key actions
    glslSandbox->keyPressed(key);
}

