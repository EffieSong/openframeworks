#include "ofApp.h"
ofSoundPlayer bgm;
Chameleon chameleon;
Chameleon chameleon2;
Element redApple(0,0);
Element grayElephant(0,0);
Element Leaf(743,424);
Element backTree(1400,0);
Element bigTree(1400,0);
Element flower(1400,0);
Element foregroundFlower(1400,0);
Element branch(0,0);
ofColor background(254,253,239);
ofColor chamColor(107,147,103);
ofColor ground(179,121,76);
ofColor appleColor(239,62,54);
ofColor leafColor(40,150,121);
ofColor yellowLeaf(225,180,29);
float sad = 0;
int emotion = 1;
int alphaFadeOut =0;
int alphaFadeIn = 255;
ofFbo fbo_fadeIn;
ofFbo fbo_fadeOut;
ofImage apple;
ofImage elephant;
ofImage scene6BG;
ofImage branchImg;
ofImage leaf;
ofImage backTreeImg;
ofImage backTreeImg2;
ofImage bigTreeImg;
ofImage bigTreeImg2;
ofImage flowerImg;
ofImage foregroundFlowerImg;
string storyStr;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(background);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    ofSetPolyMode(OF_POLY_WINDING_POSITIVE);
    
    //load sound
    bgm.load("Whisper.mp3");
    
    //load picture
    apple.load("apple.png");
    elephant.load("elephant.png");
    scene6BG.load("scene6BG.jpg");
    leaf.load("leaf.png");
    foregroundFlowerImg.load("foregroundFlower.png");
    flowerImg.load("flower.png");
    bigTreeImg.load("bigTree.png");
    bigTreeImg2.load("tree2-1.png");
    backTreeImg.load("backTree.png");
    backTreeImg2.load("tree2-2.png");
    branchImg.load("branch.png");
    
    //load font
 //   font.load("ArchitectsDaughter-Regular.ttf",16);
   font.load("GloriaHallelujah-Regular.ttf",16);
  //  font.load("IndieFlower-Regular.ttf",16);
    emotionButton.addListener(this, &ofApp::emotionButtonPressed);
   
    gui.setup();
    gui.add(volume.setup("volume",1.0,0.0,1.0));
    gui.add(emotionButton.setup("emotion"));
    gui.add(guiPos.setup("position",{ofGetWidth()/2,ofGetHeight()/2},{-500,-500},{ofGetWidth(),ofGetWidth()}));
    gui.add(guiColor.setup("color", ofColor(168,195,120), ofColor(0, 0), ofColor(255, 255)));
    gui.add(sadDegree.setup("sadDegree",10,0,10));
    gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
    
    fbo_fadeOut.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA32F);
    fbo_fadeOut.begin();
     ofClear(255, 255, 255,0);
    fbo_fadeOut.end();
    fbo_fadeIn.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA32F);
    fbo_fadeIn.begin();
        ofClear(255, 255, 255,0);
    fbo_fadeIn.end();
    
    chameleon.setCurrentPos(350, 550);
    chameleon.color = chamColor;
    chameleon2.pos.x = ofGetWidth()+chameleon.r;
    
    redApple.color = appleColor;
    redApple.r = 100;
    Leaf.r = 100;
    Leaf.color = leafColor;
    foregroundFlower.r = 100;
    flower.r = 80;
    bigTree.r = 80;
    bgm.play();

    
}

//--------------------------------------------------------------
void ofApp::update(){
     bgm.setVolume(volume);
   
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(ofGetElapsedTimef()<30) {
        drawScene1(0);
         ofSetColor(74,71,63);
         font.drawString(storyStr,832-font.stringWidth(storyStr)/2,83);
    }
    if(ofGetElapsedTimef()>30 && ofGetElapsedTimef()<60) {
        drawScene2(30);
        ofSetColor(255,253,245);
        font.drawString(storyStr,832-font.stringWidth(storyStr)/2,83);
    }
    if(ofGetElapsedTimef()>60 && ofGetElapsedTimef()<127) {
        drawScene3(60);
        ofSetColor(74,71,63);
        font.drawString(storyStr,832-font.stringWidth(storyStr)/2,83);
    }
    if(ofGetElapsedTimef()>127 && ofGetElapsedTimef()<200) {
        drawScene4(127);
        ofSetColor(74,71,63);
        font.drawString(storyStr,832-font.stringWidth(storyStr)/2,83);
    }
    
   
   
  

  //  gui.draw();
    timeString = "elapsed time: "+ofToString(ofGetElapsedTimef());
   
 //   font.drawString(timeString, 200,98);
  //  font.drawString(eventString, 200,150);
   
   
    
 
   
    
}


void ofApp::drawScene1(float time){
   // ofSetColor(ground);
     if(ofGetElapsedTimef()<6+time){
        alphaFadeOut = 0;
        chameleon.setCurrentPos(507, 362);
        redApple.pos = ofVec3f(ofGetWidth()/2 , 427);
        grayElephant.pos = ofVec3f(ofGetWidth()/2,ofGetHeight()+elephant.getHeight()/2);
    }
    if(ofGetElapsedTimef()>13+time){
        chameleon.changeColorByElement(redApple, 0.02);//The apple is red, so becomes red
    }
    if(ofGetElapsedTimef()>15+time && ofGetElapsedTimef()<19.2+time){//apple away
        chameleon.moveTo(ofVec3f(507,ofGetHeight()+elephant.getHeight()/2-530+285),1.5);
        redApple.rZ -= 1;
        redApple.pos -= ofVec3f(3.2,0);
    }
    if(ofGetElapsedTimef()>19+time){ //It rested on the elephant's back.
        chameleon.moveTo(ofVec3f(507,285),0.6);
        grayElephant.moveTo(ofVec3f(520,530), 0.6);
        ofSetColor(255);
         ofPushMatrix();
            ofTranslate(grayElephant.pos);
            ofScale(1.5, 1.5);
        elephant.draw(0-elephant.getWidth()/2,0-elephant.getHeight()/2);
        ofPopMatrix();
      }
    if(ofGetElapsedTimef()>25+time){//The elephant is grey, so it becomes grey.
        chameleon.changeColor(ofColor(138,137,143), 0.05);
    }
     
    if(ofGetElapsedTimef()>7+time){ //draw apple
        ofPushMatrix();
        ofTranslate(redApple.pos);
            ofScale(1.7, 1.7);
            ofRotateZDeg(redApple.rZ);
            ofSetColor(255);
            apple.draw(0 - apple.getWidth()/2, 0 - apple.getHeight()/2);  // draw at new 0,0
        ofPopMatrix();
    }
    chameleon.render(emotion);
    drawfadeIn();
//    if(ofGetElapsedTimef()>28+time){
//         drawfadeOut();
//        alphaFadeIn = 255;
//    }
     if(ofGetElapsedTimef()>3+time && ofGetElapsedTimef()<7+time){
         storyStr = "Once upon a time, \nthere was a chameleon.";
     }
    else if(ofGetElapsedTimef()>7+time && ofGetElapsedTimef()<12+time){
        storyStr = " One day, it lay on an apple thinking.";
    }
    else if(ofGetElapsedTimef()>12+time && ofGetElapsedTimef()<19+time){
        storyStr = "The apple was red, \nso it became red.";
    }
    else if(ofGetElapsedTimef()>19+time && ofGetElapsedTimef()<23+time){
        storyStr = "It rested on an elephant's back.";
    }
    else if(ofGetElapsedTimef()>23+time && ofGetElapsedTimef()<27+time){
        storyStr = "The elephant was grey, \nso it became grey.";
    }
    else{
        storyStr = " ";
    }
}




float speedBackTree;
float speedFrontFlower;
float speedBigTree;
float speedflower;

void ofApp::drawScene2(float time){
    chameleon.setCurrentPos(314, 527);
    chameleon.walk(0.5);
    speedBackTree = 0.0004;
    speedBigTree = 0.0008;
    speedflower = 0.0009;
    speedFrontFlower = 0.003;
        backTree.interpolateByPct(1100, 96, -300, 96, speedBackTree);
        bigTree.interpolateByPct(1000, 88, -300, 88, speedBigTree);
    if(ofGetElapsedTimef()<2+time){
        alphaFadeOut = 0;
    }
     if(ofGetElapsedTimef()> 3.000+time){
         foregroundFlower.interpolateByPct(1400, 668, -300, 668, speedFrontFlower);
     };
    if(ofGetElapsedTimef()> 5.000+time){
           flower.interpolateByPct(1400, 531, -300, 531, speedflower);
        };
    if(ofGetElapsedTimef()>8.000+time){
        chameleon.changeColor(ofColor(149,87,76), 0.05);
    }
    if(ofGetElapsedTimef()>15.000+time){
        chameleon.changeColor(ofColor(198,92,127), 0.06);
    }
    ofSetColor(34,79,91);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());//bg
    ofSetColor(255);
    backTreeImg.draw(backTree.pos.x-backTreeImg.getWidth()/2,backTree.pos.y-backTreeImg.getHeight()/2);
    ofSetColor(247,178,77);
    ofDrawRectangle(0, 445, ofGetWidth(), ofGetHeight());//ground
    ofSetColor(255);
    bigTreeImg.draw(bigTree.pos.x-bigTreeImg.getWidth()/2,bigTree.pos.y-bigTreeImg.getHeight()/2);
    chameleon.render(emotion);
    ofSetColor(255);
    flowerImg.draw(flower.pos.x-flowerImg.getWidth()/2,flower.pos.y-flowerImg.getHeight()/2);
    foregroundFlowerImg.draw(foregroundFlower.pos.x-foregroundFlowerImg.getWidth()/2,foregroundFlower.pos.y-foregroundFlowerImg.getHeight()/2);
    
    if(ofGetElapsedTimef()> 18.000+time){
        emotion = 2;
        sad += 0.04;
        if(sad >10)sad=10;
    };
//    drawfadeIn();
//    if(ofGetElapsedTimef()>28.000+time){
//        drawfadeOut();
//        alphaFadeIn = 255;
//    }
    if(ofGetElapsedTimef()>8.5+time && ofGetElapsedTimef()<15+time){
        storyStr = "Wherever it went, \nit had to keep changing colors.";
    }
    else if(ofGetElapsedTimef()>19+time && ofGetElapsedTimef()<27+time){
        storyStr = "It felt very unhappy. \nIt didn't know what its own color was.";
    }
    else{
           storyStr = " ";
       }
}

ofVec3f branchPos(-32,376);
//float rZ=0;
float groundY=1000;
ofVec3f ChamScene6Pos(350,450);

void ofApp::drawScene3(float time){
    ofSetColor(216,226,186);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());//bg
    ofSetColor(255);
    branchImg.draw(branchPos.x,branchPos.y);
    
    if(ofGetElapsedTimef()< 2.000+time)
    {
        chameleon.setCurrentPos(320, 470);
        emotion = 2;
        sad = 5;
        alphaFadeOut=0;
    }
    if(ofGetElapsedTimef()> 2.000+time && ofGetElapsedTimef()<8+time){
        chameleon.moveTo(Leaf.pos-ofVec3f(20,5), 1.0);
        chameleon.changeColorByElement(Leaf,0.06);
    }
    if(ofGetElapsedTimef()>9.000+time && ofGetElapsedTimef()<15+time){
        sad -= 0.08;
        if(sad <0)sad=0;
    }
    
    if(ofGetElapsedTimef()>20+time){//leaf change color to yellow
        ofPixelsRef leafPixels = leaf.getPixels();
        for(int y = 0; y < leaf.getHeight(); y++){
               for(int x = 0; x < leaf.getWidth(); x++){
                   ofColor color = leaf.getColor(x, y);
                   if(color.a > 50){
                       color.lerp(ofColor(252,160,20),0.1);
                       leafPixels.setColor(x, y, color);
                   }
               }
           }
        leaf.setFromPixels(leafPixels);
    }
     if(ofGetElapsedTimef()>23+time){
          chameleon.changeColor(yellowLeaf,0.04);
     }
    if(ofGetElapsedTimef()>26.50+time && ofGetElapsedTimef()<40.00+time ){
        if(groundY > 350) Leaf.rotate(0.2);
        branchPos += ofVec3f(0,-1.7,0);//drop
        groundY -= 1;
        if(groundY < 350){
            groundY = 350;
        }
    }
    if(ofGetElapsedTimef()> 33.000+time){
        emotion = 2;
        sad += 0.04;
        if(sad >10)sad=10;
    };
    if(ofGetElapsedTimef()>39.000+time &&  Leaf.pos.x>282&& chameleon.pos.x>290){                             //camera move
        chameleon.pos -= ofVec3f(1,0,0);
        Leaf.pos -= ofVec3f(1,0,0);
        branchPos -= ofVec3f(1,0,0);
    }
    if(ofGetElapsedTimef()> 46.500+time && chameleon2.pos.x>790){//chameleon2 appear
        chameleon2.pos.y = chameleon.pos.y;
        chameleon2.pos -= ofVec3f(1,0,0);
        chameleon2.walk(0.5);
    }
    if(ofGetElapsedTimef()> 45.000+time){
        sad -= 0.04;
        if(sad <0)sad=0;
    }
        
    
    //display
    ofSetColor(104, 135, 125);
    ofDrawRectangle(0, groundY, ofGetWidth(), ofGetHeight());
    ofPushMatrix();
        ofTranslate(Leaf.pos.x-leaf.getWidth()/2,Leaf.pos.y-leaf.getHeight()/2);
        ofRotateZDeg(Leaf.rZ);
        ofSetColor(255);
        leaf.draw(0,0);
    ofPopMatrix();
    
    chameleon2.color =ofColor (219,169,4);
    chameleon2.renderReverse(1);
    chameleon.render(emotion);
    drawfadeIn();
    bigTree.pos.x = 1400;
    bigTree.pct =0;
    backTree.pos.x  = 1400;
    backTree.pct = 0;
//    if(ofGetElapsedTimef()> 50.000+time){
//          drawfadeOut();
//      }
    if(ofGetElapsedTimef()>3+time && ofGetElapsedTimef()<9+time){
        storyStr = "So it found a leaf it liked \nand turned green with it. ";
    }
    else if(ofGetElapsedTimef()>9+time && ofGetElapsedTimef()<13+time){
        storyStr = "It was happy all spring and summer.";
    }
    else if(ofGetElapsedTimef()>13+time && ofGetElapsedTimef()<17+time){
        storyStr = "It thought that it had its own color.";
    }
    else if(ofGetElapsedTimef()>17+time && ofGetElapsedTimef()<23+time){
        storyStr = "However, by autumn, \nthe leaf was turning yellow.";
    }
    else if(ofGetElapsedTimef()>23+time && ofGetElapsedTimef()<27+time){
        storyStr = "It turned yellow with the leaf.";
    }
    else if(ofGetElapsedTimef()>27+time && ofGetElapsedTimef()<36.5+time){
         storyStr = "and then in winter, \nit fell from the tree with the leaf.";
     }
    else if(ofGetElapsedTimef()>36.5+time && ofGetElapsedTimef()<47+time){
        storyStr = "It fell to the ground, \nbeing so sad \nthat it did not know what to do.";
    }
    else if(ofGetElapsedTimef()>47+time && ofGetElapsedTimef()<55+time){
        storyStr = "At this time, it met another chameleon. \nThis chameleon had the same trouble.";
    }
    else if(ofGetElapsedTimef()>55+time && ofGetElapsedTimef()<58.4+time){
        storyStr = "They all had to keep changing colors.";
    }
    else if(ofGetElapsedTimef()>58.4 +time&& ofGetElapsedTimef()<67+time){
        storyStr = "However, \nthis chameleon was more clever.";
    }
    else{
           storyStr = " ";
       }
}
void ofApp::drawScene4(float time){
    chameleon.walk(0.5);
    speedBackTree = 0.0004;
    speedBigTree = 0.0008;
    speedflower = 0.0009;
    speedFrontFlower = 0.003;
        backTree.interpolateByPct(1100, 96, -300, 96, speedBackTree);
        bigTree.interpolateByPct(1000, 76, -300, 76, speedBigTree);
    if(ofGetElapsedTimef()<2+time){
        alphaFadeOut = 0;
        
    }
    if(ofGetElapsedTimef()>13.000+time){
        chameleon.changeColor(ofColor(181,52,49), 0.05);
        chameleon2.changeColor(ofColor(163,29,26), 0.05);
    }
 
    ofSetColor(247,216,170);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());//bg
    ofSetColor(255);
    backTreeImg2.draw(backTree.pos.x-backTreeImg.getWidth()/2,backTree.pos.y-backTreeImg.getHeight()/2);
    ofSetColor(211,128,38);
    ofDrawRectangle(0, 445, ofGetWidth(), ofGetHeight());//ground
      
    ofSetColor(255);
    bigTreeImg2.draw(bigTree.pos.x-bigTreeImg.getWidth()/2,bigTree.pos.y-bigTreeImg.getHeight()/2);
    chameleon.setCurrentPos(339, 549);
    chameleon2.setCurrentPos(467, 500);
    chameleon2.render2(1);
    chameleon.render3(1);
   if(ofGetElapsedTimef()> 5.000+time){
       redApple.rZ = 0;
        redApple.interpolateByPct(1500, 521, -300, 521, speedflower);
       ofPushMatrix();
                 ofTranslate(redApple.pos);
                     ofScale(1.7, 1.7);
                     ofRotateZDeg(redApple.rZ);
                     ofSetColor(255);
                     apple.draw(0 - apple.getWidth()/2, 0 - apple.getHeight()/2);  // draw at new 0,0
          ofPopMatrix();
       };

    
    if(ofGetElapsedTimef()>0 +time&& ofGetElapsedTimef()<5+time){
        storyStr = "It told it that \nthey could always walk together";
    }
    else if(ofGetElapsedTimef()>8 +time&& ofGetElapsedTimef()<16+time){
          storyStr = "So that wherever they went, \nthey would still turn red\n when they meet apples,";
      }
    else if(ofGetElapsedTimef()>17+time && ofGetElapsedTimef()<20+time){
        storyStr = "but not because of the apple,";
    }
    else if(ofGetElapsedTimef()>21+time && ofGetElapsedTimef()<30+time){
        storyStr = "just because \nthey became the color of each other.";
    }
    else{
              storyStr = " ";
          }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
   eventString = "mouseMoved = (" + ofToString(x) + ", " + ofToString(y) + ")";
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


void ofApp::drawfadeIn(){
    fbo_fadeIn.begin();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(0, 0, 0,alphaFadeIn);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    fbo_fadeIn.end();
    fbo_fadeIn.draw(0,0);
    alphaFadeIn-= 4;
    if (alphaFadeIn<0){
        fbo_fadeIn.clear();
        alphaFadeIn=0;
    }
     
}
void ofApp::drawfadeOut(){
    fbo_fadeOut.begin();
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofSetColor(0, 0,0,alphaFadeOut);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());

        fbo_fadeOut.end();
    fbo_fadeOut.draw(0,0);
    alphaFadeOut += 4;
    if (alphaFadeOut>255){
        fbo_fadeOut.clear();
        alphaFadeOut = 255;
    }
}

void Chameleon:: walk(float step){
    if(foot_back < -7.0 || foot_back >2.0 )dr *= -1;
    foot_back -= step*dr;
    foot_front += step*dr;
}



void Chameleon::changeColorByElement(Element object,float a){
    float dis = pos.distance(object.pos);
    if (dis < r+object.r){
        color.lerp(object.color,a);
    }
    //cout<< dis << endl;
}

void Chameleon::changeColor(ofColor targetColor,float a){
    color.lerp(targetColor,a);
};

//Element
void Chameleon::setCurrentPos(int x, int y){
    pos.x = x;
    pos.y = y;
}
void Chameleon::setTargetPos(int x, int y){
    targetPos.x = x;
    targetPos.y = y;
}
//
void Chameleon::zenoToPoint(int x, int y,float catchUpSpeed){
    pos.x = catchUpSpeed * x + (1-catchUpSpeed) * pos.x;
    pos.y = catchUpSpeed * y + (1-catchUpSpeed) * pos.y;
}

void Chameleon::moveTo(ofVec3f target, float scale){
    ofVec3f speed = target-pos;
    speed.getNormalized();
    speed.scale(scale);
    pos += speed;
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
        ofCurveVertex(foot_back,10);//
        ofCurveVertex(-15,0);
        ofCurveVertex(0,0);
        ofCurveVertex(5,10);
    ofEndShape();
    ofBeginShape();
        ofCurveVertex(15,0);
        ofCurveVertex(30,0);
        ofCurveVertex(foot_front,10);//
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
    //   happySound.play();
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
     //  sadSound.play();
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
void Chameleon::render2(int emotion){
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
    
    ofBeginShape();
        ofCurveVertex(-15,0);
        ofCurveVertex(0,0);
        ofCurveVertex(foot_back,10);//
        ofCurveVertex(-15,0);
        ofCurveVertex(0,0);
        ofCurveVertex(5,10);
    ofEndShape();
    ofBeginShape();
        ofCurveVertex(15,0);
        ofCurveVertex(30,0);
        ofCurveVertex(foot_front,10);//
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
    //   happySound.play();
    //eyes
       ofSetColor(255, 255, 255);
       ofDrawCircle(29, -65, 30);
       ofSetColor(10,10,10);
       ofDrawCircle(26
                    
                    , -58, 6);
    //mouth
       ofSetColor(10, 10, 10);
       ofSetLineWidth(3);
       ofDrawLine(90,-25,75, -20);
       ofDrawLine(75, -20,60,-23);
            
    break;

   case 2://///sad
     //  sadSound.play();
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
void Chameleon::renderReverse(int emotion){
    ofSetColor(color);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotateYDeg(180);
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
        ofCurveVertex(foot_back,10);//
        ofCurveVertex(-15,0);
        ofCurveVertex(0,0);
        ofCurveVertex(5,10);
    ofEndShape();
    ofBeginShape();
        ofCurveVertex(15,0);
        ofCurveVertex(30,0);
        ofCurveVertex(foot_front,10);//
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
    //   happySound.play();
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
     //  sadSound.play();
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
void Chameleon::render3(int emotion){
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
        ofCurveVertex(foot_back,10);//
        ofCurveVertex(-15,0);
        ofCurveVertex(0,0);
        ofCurveVertex(5,10);
    ofEndShape();
    ofBeginShape();
        ofCurveVertex(15,0);
        ofCurveVertex(30,0);
        ofCurveVertex(foot_front,10);//
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
   // eyes
        ofSetColor(255, 255, 255);
        ofDrawCircle(29, -65, 30);
        ofSetColor(10,10,10);
        ofDrawCircle(43, -56, 6);
    //mouth
        ofSetColor(10, 10, 10);
        ofSetLineWidth(3);
        ofDrawLine(90,-20,80, -18);
        ofDrawLine(80, -18 ,60,-23);
    
     case 1:    //happy/////////
    //   happySound.play();
    //eyes
       ofSetColor(255, 255, 255);
       ofDrawCircle(29, -65, 30);
       ofSetColor(10,10,10);
       ofDrawCircle(40, -70, 6);
    //mouth
       ofSetColor(10, 10, 10);
       ofSetLineWidth(3);
       ofDrawLine(90,-25,75, -20);
       ofDrawLine(75, -20,60,-23);
            
    break;

   case 2://///sad
     //  sadSound.play();
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

void Element::interpolateByPct(int x1, int y1, int x2, int y2, float speed){
    pct += speed;        // increase by a certain amount
    if (pct > 1) {
        pct = 1;
    }
    pos.x = (1-pct) * x1 + (pct) * x2;
    pos.y = (1-pct) * y1 + (pct) * y2;
   // cout<<pct<<endl;
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

void Element::renderApple(){
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofScale(1.5, 1.5);  // can be 3 dimensional
       ofRotateZDeg(rZ);
       ofSetColor(255);
       apple.draw(0 - apple.getWidth()/2, 0 - apple.getHeight()/2);  // draw at new 0,0
     ofPopMatrix();
}

void Element::appleMove(){
    rZ -=5;
    redApple.interpolateByPct(ofGetWidth(),450,520,450,0.005f);
    if(pct == 1)rZ = 0;
}
void Element::appleStopMove(){
    rZ = 0;
}
void Element::renderElephant(){
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofScale(1.8, 1.8);  // can be 3 dimensional
       ofRotateZDeg(rZ);
       ofSetColor(255);
       elephant.draw(0 - elephant.getWidth()/2, 0 - elephant.getHeight()/2);  // draw at new 0,0
     ofPopMatrix();
}
void Element::elephantMove(){
  grayElephant.interpolateByPct(ofGetWidth(),250,520,250,0.002f);
}

int b = 1;
void Element::rotate(float a){
    rZ += a*b;
    if(rZ > 10 || rZ<-10){
        b *= -1;
    }
}
void Element::stopRotate(){
    rZ =0;
}
void Element::moveTo(ofVec3f target, float scale){
    ofVec3f speed = target-pos;
    speed.getNormalized();
    speed.scale(scale);
    pos += speed;
}


