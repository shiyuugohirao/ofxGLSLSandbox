#pragma once

#include "ofMain.h"
#include "ofxGLSLSandbox.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

    ofxGLSLSandbox *glslSandbox;
};
