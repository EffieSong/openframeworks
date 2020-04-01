#include "ofApp.h"
ofSoundPlayer happySound;
ofSoundPlayer sadSound;
ofSoundPlayer surpriseSound;
ofSoundPlayer angrySound;
Chameleon chameleon(200,200);
//ofColor chamColor(190,224,130);
//ofColor background(254,239,202);
ofColor background(63,69,74);
ofColor chamColor(168,195,120);
int sad ;
int emotion = 1;
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(background);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    ofSetPolyMode(OF_POLY_WINDING_POSITIVE);

    happySound.load("happy.wav");
    sadSound.load("sad.wav");
    surpriseSound.load("surprise.wav");
    angrySound.load("angry.wav");
  
    
    emotionButton.addListener(this, &ofApp::emotionButtonPressed);
   
    gui.setup();
    gui.add(volume.setup("volume",1.0,0.0,1.0));
    gui.add(emotionButton.setup("emotion"));
  gui.add(pos.setup("position",{ofGetWidth()/2,ofGetHeight()/2},{0,0},{ofGetWidth(),ofGetWidth()}));
    gui.add(color.setup("color", ofColor(168,195,120), ofColor(0, 0), ofColor(255, 255)));
    gui.add(sadDegree.setup("sadDegree",10,0,10));
    gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
    
}
float step = 0.5;
float foot_1 = 2.0;
float foot_2 = 23.0;
//--------------------------------------------------------------
void ofApp::update(){
     happySound.setVolume(volume);
     sadSound.setVolume(volume);
     surpriseSound.setVolume(volume);
     angrySound.setVolume(volume);
    
     chameleon.setTargetPos(pos->x, pos->y);
     chameleon.color = color;
     sad = sadDegree;
    foot_1 -= step;
    foot_2 += step;
    if(foot_1 < -7.0 || foot_1 >2.0 ){
        step *= -1;
    }
    cout<<step<<endl;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
   chameleon.render(emotion);
   chameleon.interpolateByPct(0.03);
    


 
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
void ofApp::emotionButtonPressed(){
    emotion = emotion+1;
    if( emotion>4){
        emotion = 1;
    }

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




void Chameleon::changeColor(Element object){
    float dis = pos.distance(object.pos);
    if (dis < r+object.r){
        color.lerp(object.color,0.06);
    }
    cout<< dis << endl;
}


//Element

void Chameleon::setTargetPos(int x, int y){
    targetPos.x = x;
    targetPos.y = y;
}
//
void Chameleon::zenoToPoint(float catchUpSpeed){
    pos.x = catchUpSpeed * targetPos.x + (1-catchUpSpeed) * pos.x;
    pos.y = catchUpSpeed * targetPos.y + (1-catchUpSpeed) * pos.y;
}

void Chameleon::interpolateByPct(float speed){
    pct += speed;        // increase by a certain amount
    if (pct > 1) {
        pct = 1;
    }
    pos.x = (1-pct) * initialPos.x + (pct) * targetPos.x;
    pos.y = (1-pct) * initialPos.y + (pct) * targetPos.y;
    
}

void Chameleon::render(int emotion){
    ofSetColor(color);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    
//body
        ofBeginShape();
        for (int i = 0; i < 20; i++){
            float anglef = ((float)i / 19.0f) * PI;
            float x =  120 * cos(anglef);
            float y = - 110 * sin(anglef);
            ofVertex(x,y);
        }
        ofEndShape();
    
//tail
        ofBeginShape();
           for (int i = 0; i < 20; i++){
            float anglef = ((float)i / 19.0f) * PI/2;
            float x =  -20-100 * cos(anglef);
            float y =  100 * sin(anglef);
            ofVertex(x,y);
        }
           for (int i = 0; i < 20; i++){
        
            float anglef = ((float)i / 19.0f) * PI-PI/2;
            float x =  -20+40 * cos(anglef);
            float y =  60-40 * sin(anglef);
            ofVertex(x,y);
        }
           for (int i = 0; i < 20; i++){
        
            float anglef = ((float)i / 19.0f) * PI-PI/2;
            float x =  -20+20 * cos(anglef);
            float y =  40+20 * sin(anglef);
            ofVertex(x,y);
        }
           for (int i = 0; i < 20; i++){
        
            float anglef = ((float)i / 19.0f) * PI-PI/2;
            float x =  -20-35 * cos(anglef);
            float y =  25-35 * sin(anglef);
            ofVertex(x,y);
        }
         ofEndShape();
//foot
    
    ofBeginShape();
        ofCurveVertex(-15,0);
        ofCurveVertex(0,0);
        ofCurveVertex(foot_1,10);//
        ofCurveVertex(-15,0);
        ofCurveVertex(0,0);
        ofCurveVertex(5,10);
    ofEndShape();
    ofBeginShape();
        ofCurveVertex(15,0);
        ofCurveVertex(30,0);
        ofCurveVertex(foot_2,10);//
        ofCurveVertex(15,0);
        ofCurveVertex(30,0);
        ofCurveVertex(35,10);
    ofEndShape();

//head

    ofTranslate(80,0);
    ofBeginShape();
        ofCurveVertex(0,0);//4
        ofCurveVertex(0,-120);//top 1
        ofCurveVertex(50,-96);//2
        ofCurveVertex(98,-25);//mouth 3
        ofCurveVertex(0,0);//4
        ofCurveVertex(0,-120);//1
        ofCurveVertex(50,-96);//2
    ofEndShape();
 
    switch (emotion) {
    default :
     happySound.play();
   // eyes
        ofSetColor(255, 255, 255);
        ofDrawCircle(29, -65, 30);
        ofSetColor(10,10,10);
        ofDrawCircle(34, -65, 6);
    //mouth
        ofSetColor(10, 10, 10);
        ofSetLineWidth(3);
        ofDrawLine(90,-20,80, -18);
        ofDrawLine(80, -18 ,60,-23);
    
     case 1:    //happy/////////
       happySound.play();
    //eyes
       ofSetColor(255, 255, 255);
       ofDrawCircle(29, -65, 30);
       ofSetColor(10,10,10);
       ofDrawCircle(34, -65, 6);
    //mouth
       ofSetColor(10, 10, 10);
       ofSetLineWidth(3);
       ofDrawLine(90,-25,75, -20);
       ofDrawLine(75, -20,60,-23);
            
    break;

   case 2://///sad
       sadSound.play();
 //eye
       ofSetColor(255, 255, 255);
       ofBeginShape();
        for (int i = 0; i < 20; i++){
       
                 float anglef = ((float)i / 19.0f) * (2-ofMap(sad,0,10,0,0.9))*PI-PI*(0.7-ofMap(sad,0,10,0,0.45));
                 float x =  29+30 * cos(anglef);
                 float y =  -65+30 * sin(anglef);
                 ofVertex(x,y);
             }
       ofEndShape();
           ofSetColor(10,10,10);
           ofDrawCircle(34+ofMap(sad,0,10,0,5), -65+ofMap(sad,0,10,0,14), 6);
         //  ofDrawCircle(39, -51, 6);
//mouth
           ofSetColor(10, 10, 10);
           ofSetLineWidth(3);
           ofDrawLine(90,-25,75, -20-sad);
           ofDrawLine(75, -20-sad,62,-23+ofMap(sad,0,10,0,5));
    break;
            
    case 3:
    //angry///////////////
            angrySound.play();
             //eye
            ofSetColor(255, 255, 255);
        ofBeginShape();
              for (int i = 0; i < 20; i++){
            
                        float anglef = ((float)i / 19.0f) * 1.2*PI+PI*0.1;
                        float x =  29+30 * cos(anglef);
                        float y =  -65+30 * sin(anglef);
                        ofVertex(x,y);
                    }
        ofEndShape();
            ofSetColor(10,10,10);
            ofDrawCircle(39, -60, 6);
    //mouth
            ofSetColor(10, 10, 10);
            ofSetLineWidth(3);
            ofDrawLine(90,-25,75, -36);
            ofDrawLine(75, -36 ,62,-18);
            break;
    case 4:
       //surprise///////////////
            surpriseSound.play();
        //eye
           ofSetColor(255, 255, 255);
           ofDrawCircle(29, -65, 30);
           ofSetColor(10,10,10);
           ofDrawCircle(34, -65, 6);
    //mouth
            ofSetColor(10, 10, 10);
            ofNoFill();
            ofSetLineWidth(3);
            ofDrawEllipse(70,-25,20,20);
            ofFill();
    break;
    };
            

        ofPopMatrix();
        
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





