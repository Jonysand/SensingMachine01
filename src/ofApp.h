#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);

        int width = 640;
        int height = 480;
        ofxPanel guiPanel;
    
        // offset tracking
        ofVideoGrabber cam;
        ofxCv::RunningBackground background;
        ofImage thresholded;
        ofParameter<bool> resetBackground;
        ofParameter<float> learningTime, thresholdValue;
        ofPixels thre_pix;
        int centerX;
        int centerY;
        int centerX_old;
        int centerY_old;
    
        // animation
        ofImage resultImg;
        const static int rain_amount=20;
        vector<float> rains [rain_amount];
        // radius of the rain drop
        float r = 3;
        // initial velocity
        float init_v = 0;
        float obj_Xv = 0;
        float obj_Yv = 0;
        // magnification of velocity&acceleration
        float mag_v = 1;
        float mag_g = 1;
        // initial acceleration
        float g = 0.5;
};
