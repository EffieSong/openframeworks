#include "ofApp.h"
#include <iostream>
using namespace std;
int centerX = 512;
int centerY = 385;
//function items[2] = {drawMaple(),drawApple()};



//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(255,255,255);
    ofSetFrameRate(60);
    ofSetPolyMode(OF_POLY_WINDING_POSITIVE);
    gui.setup();
    gui.add(uiMode.set("mode",0,0,3));
    gui.add(uiPositionX.set("position x",ofVec4f(0,10,20,0),ofVec4f(),ofVec4f(ofGetWidth())));
    gui.add(uiPositionY.set("position y",ofVec4f(0),ofVec4f(0),ofVec4f(ofGetHeight())));
}

//--------------------------------------------------------------
void ofApp::update(){
    if(uiMode == 0){
        ofSetPolyMode(OF_POLY_WINDING_POSITIVE);
    }else if (uiMode == 1){
        ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    }else if (uiMode == 2){
        ofSetPolyMode(OF_POLY_WINDING_ODD);
    }else if (uiMode == 3){
        ofSetPolyMode(OF_POLY_WINDING_ABS_GEQ_TWO);
    }
 

}

int i = 1;
//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(10, 10, 10);
    ofDrawBitmapString(ofToString(mouseX)+" "+ofToString(mouseY), 20,20);
    int frameNum = ofGetFrameNum();
    // cout << ofGetFrameNum();
    
    if(frameNum % 120 == 0){
         i = i + 1;
        if(i>4){
            i = 1;
        }
    };
    
    switch (i) {
      case 1:
    happiness();
        break;
            
      case 2:
    sadness();
        break;
           
        case 3:
    surprise();
       break;
            
        case 4:
    anger();
      break;
    };


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

//--------------------------------------------------------------
void ofApp::drawApple( ){
    ofSetColor(255, 0, 0);
       ofFill();
       ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 60);
       ofSetColor(40, 40, 20);
       ofFill();
       ofDrawBezier(ofGetWidth()/2-20, ofGetHeight()/2-40, 501, 353, 510, 353, ofGetWidth()/2+20, ofGetHeight()/2-40);
       
       ofSetColor(40, 40, 20);
       ofFill();
       ofSetRectMode(OF_RECTMODE_CENTER); //set rectangle mode to the center
       ofDrawRectangle(centerX, centerY-60, 3, 40);
       

}
void ofApp::drawMaple( ){
    ofSetColor(100,80, 50);
    ofFill();
    ofSetRectMode(OF_RECTMODE_CENTER); //set rectangle mode to the center
    ofDrawRectangle(centerX, centerY+130, 10, 120);
      ofSetColor(255, 100, 50);
        ofFill();
        ofBeginShape();
    //    ofVertex(uiPositionX -> x, uiPositionY -> x);
    //    ofVertex(uiPositionX -> y, uiPositionY -> y);
    //    ofVertex(uiPositionX -> z, uiPositionY -> z);
    //    ofVertex(uiPositionX -> w, uiPositionY -> w);
         ofVertex(centerX,centerY-150);
        ofVertex(centerX-70,centerY-50);
        ofVertex(centerX-150,centerY-80);
        ofVertex(centerX-150,centerY);
        ofVertex(centerX-70,centerY+50);
        ofVertex(centerX-110,centerY+100);
        ofVertex(centerX-70,centerY+130);
        ofVertex(centerX,centerY+80);
         ofVertex(centerX+70,centerY+130);
         ofVertex(centerX+110,centerY+100);
        ofVertex(centerX+70,centerY+50);
        ofVertex(centerX+150,centerY);
        ofVertex(centerX+150,centerY-80);
        ofVertex(centerX+70,centerY-50);
        ofEndShape(true);
     
}
void ofApp::drawTree( ){
    ofSetColor(150, 255, 150);
    ofFill();
    ofDrawTriangle(centerX, centerY-150, centerX-60,centerY, centerX+60, centerY);
    ofSetColor(100,80, 50);
    ofFill();
    ofSetRectMode(OF_RECTMODE_CENTER); //set rectangle mode to the center
    ofDrawRectangle(centerX, centerY+50, 20, 100);
}

void ofApp::drawChameleon( ){
    ofSetColor(150, 200, 150);
    ofFill();
    ofDrawCircle(centerX, centerY, 60);
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawCircle(centerX+30, centerY+10, 40);
    ofSetColor(100, 200, 100);
    ofFill();
    ofDrawTriangle(centerX+40, centerY-50-40, centerX+40-34, centerY-50+20, centerX+40+34, centerY-50+20);
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawCircle(centerX+50, centerY-40, 6);
}
void ofApp::happiness( ){
    
    ofSetColor(150, 200, 150);
    ofFill();
    ofDrawCircle(centerX, centerY, 120);
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawCircle(centerX+45, centerY+15, 80);
    ofSetColor(100, 200, 100);
    ofFill();
    ofDrawTriangle(centerX+80, centerY-100-80, centerX+80-68, centerY-100+40, centerX+80+68, centerY-100+40);
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawCircle(578, 287, 6);
    ofDrawCircle(611, 287, 6);
     ofDrawBezier(578, 300, 600, 311, 600, 311, 611, 300);
    
}
void ofApp::sadness(){
    
    ofSetColor(150, 200, 150);
    ofFill();
    ofDrawCircle(centerX, centerY, 120);
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawCircle(centerX+45, centerY+15, 80);
    ofSetColor(100, 200, 100);
    ofFill();
    ofDrawTriangle(centerX+80, centerY-100-80, centerX+80-68, centerY-100+40, centerX+80+68, centerY-100+40);
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawCircle(578, 287, 6);
    ofDrawCircle(611, 287, 6);
    ofDrawBezier(578, 311, 600, 300, 600, 300, 611, 311);
    
}
void ofApp::surprise(){
    
    ofSetColor(150, 200, 150);
    ofFill();
    ofDrawCircle(centerX, centerY, 120);
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawCircle(centerX+45, centerY+15, 80);
    ofSetColor(100, 200, 100);
    ofFill();
    ofDrawTriangle(centerX+80, centerY-100-80, centerX+80-68, centerY-100+40, centerX+80+68, centerY-100+40);
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawCircle(578, 287, 6);
    ofDrawCircle(611, 287, 6);
    ofDrawEllipse(593, 311, 10, 20);

    
}
    ofPolyline polyline1, polyline2;
    ofPoint point1(578,287);
ofPoint point2(611,287);
void ofApp::anger(){
    
    ofSetColor(150, 200, 150);
    ofFill();
    ofDrawCircle(centerX, centerY, 120);
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawCircle(centerX+45, centerY+15, 80);
    ofSetColor(100, 200, 100);
    ofFill();
    ofDrawTriangle(centerX+80, centerY-100-80, centerX+80-68, centerY-100+40, centerX+80+68, centerY-100+40);
    ofSetColor(255, 255, 255);
    ofFill();
//    ofDrawCircle(578, 287, 6);
//    ofDrawCircle(611, 287, 6);
    ofSetColor(ofColor::blue);
    polyline1.arc(point1,8,6,0,240);
    ofSetColor(ofColor::red);
    polyline1.draw();

    // draw an line, then an semi-circle in red
    //polyline2.lineTo(300, 50);
    polyline2.arc(point2,8,6,-60,180);
    
    polyline2.draw();
     ofSetColor(255, 255, 255);
    ofFill();
    ofDrawBezier(578, 311, 600, 300, 600, 300, 611, 311);

   // ofDrawBezier(578, 311, 600, 300, 600, 300, 611, 311);
    
}
