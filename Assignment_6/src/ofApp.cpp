#include "ofApp.h"
ofPoint myMouse;
    ofFbo fbo;
Element chameleon(600,400);
Element leaf(200,400);
ofColor leafColor(244, 122, 47);
ofColor chamColor(133,120,76);

int alpha = 0;

bool drawfbo  = false;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(240,212,138);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofSetCircleResolution(128);
    ofSetPolyMode(OF_POLY_WINDING_POSITIVE);
    
    font.load("Montserrat-Medium.ttf",50);
    text = "Chameleon";
    
    fbo.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA32F);
    fbo.begin();
      ofClear(255, 255, 255,0);
    fbo.end();
    
    leaf.color = leafColor;
    chameleon.color = chamColor;
    chameleon.r = 40;
    leaf.r = 150;
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
   // fbo.draw(0, 0);
    ofSetColor(185, 113, 37);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofDrawRectangle(0, ofGetHeight()*0.7, ofGetWidth(), ofGetHeight());
    
    leaf.renderLeaf();
    leaf.interpolateByPct(0.1f);
    
    chameleon.renderChameleon();
    chameleon.zenoToPoint(0.06);
    chameleon.changeColor(leaf);
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    drawFbo(drawfbo);
    
    
  

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
//    int step = 10;
//    if(key == 'w') myMouse.y = myMouse.y - step;
//    if(key == 's') myMouse.y = myMouse.y + step;
//    if(key == 'a') myMouse.x = myMouse.x - step;
//    if(key == 'd') myMouse.x = myMouse.x + step;
    
    int step = 100;
    leaf.pct = 0;
    leaf.initialPos = leaf.pos;
    if(key == OF_KEY_UP) leaf.setTargetPos(leaf.initialPos.x,leaf.initialPos.y-step);
    if(key == OF_KEY_DOWN) leaf.setTargetPos(leaf.initialPos.x,leaf.initialPos.y+step);
    if(key == OF_KEY_LEFT) leaf.setTargetPos(leaf.initialPos.x-step,leaf.initialPos.y);
    if(key == OF_KEY_RIGHT) leaf.setTargetPos(leaf.initialPos.x+step,leaf.initialPos.y);
   
 
        
  
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
   if(key == 'f'){
             drawfbo = true;
          }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
 
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    chameleon.setTargetPos(x, y);

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

void ofApp::drawFbo(bool draw){
    if(draw){
        alpha += 5;
        if (alpha>255)alpha = 255;
        fbo.begin();
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofSetColor(15, 10, 10,alpha);
            ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
            ofSetColor(255, 230, 200,alpha);
            font.drawString(text, ofGetWidth()/2-font.stringWidth(text)/2, ofGetHeight()/2);

        fbo.end();
        fbo.draw(0,0);
    }
    
}




void Element::changeColor(Element object){
    float dis = chameleon.pos.distance(object.pos);
    if (dis < chameleon.r+object.r){
        chameleon.color.lerp(object.color,0.06);
    }
    cout<< dis << endl;
}












//Element

void Element::setTargetPos(int x, int y){
    targetPos.x = x;
    targetPos.y = y;
}
//
void Element::zenoToPoint(float catchUpSpeed){
    pos.x = catchUpSpeed * targetPos.x + (1-catchUpSpeed) * pos.x;
    pos.y = catchUpSpeed * targetPos.y + (1-catchUpSpeed) * pos.y;
}

void Element::interpolateByPct(float speed){
    pct += speed;        // increase by a certain amount
    if (pct > 1) {
        pct = 1;
    }
    pos.x = (1-pct) * initialPos.x + (pct) * targetPos.x;
    pos.y = (1-pct) * initialPos.y + (pct) * targetPos.y;
    
}

void Element::renderChameleon(){

    ofSetColor(color);
    ofFill();
    ofDrawCircle(pos,60);
     
    ofSetColor(240,212,138);
    ofFill();
    ofDrawCircle(pos+ofVec3f(30,10), 40);
       
    ofSetColor(color.r-50,color.g,color.b-50);
    ofFill();
    ofDrawTriangle(pos+ofVec3f(40,-90), pos+ofVec3f(6,-30), pos+ofVec3f(74,-30));
      
    ofSetColor(240,240,238);
    ofFill();
    ofDrawCircle(pos+ofVec3f(50,-40), 6);
}
int centerX;
int centerY;

void Element::renderLeaf(){
    centerX = pos.x;
    centerY = pos.y;
    ofSetColor(100,80, 50);
    ofFill();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawRectangle(pos+ofVec3f(0,130), 10, 120);
    
    ofSetColor(color);
    ofFill();
    ofBeginShape();
//        ofVertex(pos+ofVec3f(0,-150));
//        ofVertex(pos+ofVec3f(-70,-50));
//        ofVertex(pos+ofVec3f(-150,-80));
//        ofVertex(pos+ofVec3f(-150,0));
//        ofVertex(pos+ofVec3f(-70,50));
//        ofVertex(pos+ofVec3f(-110,100));
//        ofVertex(pos+ofVec3f(-70,-130));
//        ofVertex(pos+ofVec3f(0,80));
//        ofVertex(pos+ofVec3f(70,130));
//        ofVertex(pos+ofVec3f(110,100));
//        ofVertex(pos+ofVec3f(70,50));
//        ofVertex(pos+ofVec3f(150,0));
//        ofVertex(pos+ofVec3f(150,-80));
//        ofVertex(pos+ofVec3f(70,-50));
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







