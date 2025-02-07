#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(winWidth, winHeight);
    ofSetBackgroundColor(0);
    //-------------
    // generating drops
    //-------------
    srand((unsigned)time(NULL));
    for(int i=0; i<drops_amount; i++){
        float rand_depth = rand()%winHeight * pow((-1), rand()%2);
        aDrop drop(rand()%winWidth, rand()%winHeight, rand_depth, init_v, init_v, init_v);
        drops[i] = drop;
    }
    
    cam.setup(width, height);
    
    // background subtracktion
    BGSdetector = bgsDetector(winWidth, winHeight, width, height);
    // color object detection
//    COLORdetector = colorDetector(width, height);
}



//--------------------------------------------------------------
void ofApp::update(){
    //----------------
    // offset tracking
    //----------------
    cam.update();
    if(cam.isFrameNew()) {
        // background subtracktion
        auto obj_result_BGS = BGSdetector.detectMove(cam);
        float obj_X_BGS = get<0>(obj_result_BGS);
        float obj_Y_BGS = get<1>(obj_result_BGS);
//        auto obj_result_COLOR = COLORdetector.detectMove(cam);
//        float obj_X_COLOR = get<0>(obj_result_COLOR);
//        float obj_Y_COLOR = get<1>(obj_result_COLOR);
//        obj_X = (obj_X_BGS+obj_X_COLOR)/2;
//        obj_Y = (obj_Y_BGS+obj_Y_COLOR)/2;
            obj_X = obj_X_BGS;
            obj_Y = obj_Y_BGS;
//            obj_X=0;
//            obj_Y=0;
    }
    
    
    //-------------
    // falling rain
    //-------------
    for(int i=0; i<drops_amount; i++){
        //----------------
        // movement control
        //----------------
        
        // update 3D space ratios
        drops[i].space_ratio = winHeight/(winHeight-drops[i].cord_d);
        drops[i].size_ratio = drops[i].cord_d/winHeight;
        
        // update velocity
        drops[i].updateThroughVelocity(g*mag_g, obj_X*winHeight/(winHeight-drops[i].cord_d), obj_Y*winHeight/(winHeight-drops[i].cord_d), obj_D);

        
        // go outside and reborn
        drops[i].setReborn(winWidth, winHeight);
        
        // rebounce
//        drops[i].setRebounce(winWidth, winHeight);
        
        // update position
        drops[i].updatePosition(r, mag_v, winWidth, winHeight);
    }
}






//--------------------------------------------------------------
void ofApp::draw(){
    //-------
    // camera
    //-------
//    BGSdetector.draw(winWidth, winHeight);
//    COLORdetector.draw(cam, winWidth, winHeight);
//    guiPanel = COLORdetector.guiPanel;
//    guiPanel.draw();
    
    
    //-------------
    // draw drops
    //-------------
    // draw each drop
    ofEnableAlphaBlending();
    for(int i=0; i<drops_amount; i++){
        int redius = r * drops[i].space_ratio;
        int transparency = int( 255*(1-abs(drops[i].size_ratio)));
        ofSetColor(255, 255, 255, transparency);
        ofDrawCircle(drops[i].cord_x, drops[i].cord_y,drops[i].cord_d, redius);
    }
    ofDisableAlphaBlending();
    // draw lines
//    for(int i=0; i<drops_amount; i++){
//        for(int j=i; j<drops_amount; j++){
//            if( sqrt(
//                     pow((drops[i].cord_x-drops[j].cord_x), 2)+
//                     pow((drops[i].cord_y-drops[j].cord_y), 2)+
//                     pow((drops[i].cord_d-drops[j].cord_d), 2)
//                     )<=line_thresh ){
//                ofDrawLine(drops[i].cord_x, drops[i].cord_y, drops[j].cord_x, drops[j].cord_y);
//            }
//        }
//    }
}



void ofApp::mousePressed(int x, int y, int button){
    COLORdetector.pickColor(x, y, cam);
    COLORdetector.autoCorrectThreshold(cam);
}



void ofApp::keyPressed(int key){
    if (key=='='){
        for(int i=0; i<drops_amount; i++){
            drops[i].cord_d+=10;
        }
    }
    if (key=='-'){
        for(int i=0; i<drops_amount; i++){
            drops[i].cord_d-=10;
        }
    }
}
