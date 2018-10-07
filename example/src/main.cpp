#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLWindowSettings settings;
//    settings.setGLVersion(3, 2);
    settings.setGLVersion(2, 1); //sandbox
    settings.setSize(720, 720);
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
