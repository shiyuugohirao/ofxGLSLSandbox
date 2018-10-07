//
//  ofxGLSLSandbox.h
//  myGLSLSandbox
//
//  Created by Tadokoro Atsushi on 2013/02/20.
//
//

#pragma once
#include "ofMain.h"

class ofxGLSLSandbox {
private:
    ofShader shader;
    string shaderfile;
    long lastUpdateTime;
    float width, height;
    ofPoint mouse;
    ofFbo fbo;
    bool bAutoUpdate;
    bool bAutoMouse;

public:
    ofxGLSLSandbox(int width = 512, int height = 384, bool bAutoUpdate=true, bool bAutoMouse=true);
    virtual ~ofxGLSLSandbox();
    void setResolution(int width, int height);
    void loadFiles(const string& shaderfile);
    void loadFile(const string& shaderfile, GLenum type=GL_FRAGMENT_SHADER);
    void openFile(const string& shaderfile);
    void draw();
    void keyPressed(int key);
    void mouseMoved(int x, int y);
    void mouseMoved(ofMouseEventArgs &e);
    void checkFile(ofEventArgs &e);

};
