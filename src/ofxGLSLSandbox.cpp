//
//  ofxGLSLSandbox.cpp
//  myGLSLSandbox
//
//  Created by Tadokoro Atsushi on 2013/02/20.
//
//

#include "ofxGLSLSandbox.h"

ofxGLSLSandbox::ofxGLSLSandbox(int _width, int _height, bool bAutoUpdate, bool bAutoMouse){
    width = _width;
    height = _height;
    fbo.allocate(width, height);
    this->bAutoUpdate = bAutoUpdate;
    this->bAutoMouse  = bAutoMouse;
    ofAddListener(ofEvents().update, this, &ofxGLSLSandbox::checkFile);
    ofAddListener(ofEvents().mouseMoved, this, &ofxGLSLSandbox::mouseMoved);
}
ofxGLSLSandbox::~ofxGLSLSandbox(){
    ofRemoveListener(ofEvents().update, this, &ofxGLSLSandbox::checkFile);
    ofRemoveListener(ofEvents().mouseMoved, this, &ofxGLSLSandbox::mouseMoved);
}

void ofxGLSLSandbox::setResolution(int _width, int _height){
    width = _width;
    height = _height;
    fbo.allocate(width, height);
}

void ofxGLSLSandbox::loadFiles(const string& shaderfile){
    this->shaderfile = ofToDataPath(shaderfile, true);
    shader.load(shaderfile);
}

//[*] type = GL_FRAGMENT_SHADER / GL_VERTEX_SHADER  etc.
void ofxGLSLSandbox::loadFile(const string& shaderfile, GLenum type){
    this->shaderfile = ofToDataPath(shaderfile, true);
    shader.setupShaderFromFile(type, shaderfile);
    shader.linkProgram();
}

void ofxGLSLSandbox::checkFile(ofEventArgs &e){
    if(!bAutoUpdate) return;
    if(ofFile::doesFileExist(shaderfile)){
        long latestUpdate = std::filesystem::last_write_time(shaderfile);
        if (lastUpdateTime != latestUpdate){
            cout<<"[ofxGLSLSandbox ] update shaderfile!"<<endl;
            lastUpdateTime = latestUpdate;
            loadFile(shaderfile);
        }
    }else{
        cout<<"[ofxGLSLSandbox ] not found "+shaderfile<<endl;
    }
}

void ofxGLSLSandbox::openFile(const string& shaderfile){
    string command = "open " + shaderfile;
    system(command.c_str());
}

void ofxGLSLSandbox::draw(){
    float resolution[] = {width, height};
    float mousePoint[] = {mouse.x, mouse.y};
    float time = ofGetElapsedTimef();
    
    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform2fv("mouse", mousePoint);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    
    fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
}

void ofxGLSLSandbox::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'o': // Open shader file on external editor.
            openFile(shaderfile);
            break;
        case 'r': // Reload shader
            loadFile(shaderfile);
            break;
        default:
            break;
    }
}

void ofxGLSLSandbox::mouseMoved(int x, int y){
    mouse.x = float(x) / width * (width / ofGetWidth());
    mouse.y = 1.0 - float(y) / height * (height / ofGetHeight());
}
void ofxGLSLSandbox::mouseMoved(ofMouseEventArgs &e){
    if(!bAutoMouse) return;
    mouse.x = float(e.x) / width * (width / ofGetWidth());
    mouse.y = 1.0 - float(e.y) / height * (height / ofGetHeight());
}
