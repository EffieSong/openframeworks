#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
        void happiness();
        void sadness();
        void surprise();
        void anger();
        void emotionButtonPressed();
    
        void drawfadeIn();
        void drawfadeOut();
        void drawScene1(float time);
        void drawScene2(float time);
        void drawScene3(float time);
        void drawScene4(float time);
        void drawStoryStr(float time);
    
    ofxFloatSlider volume;
    ofxButton emotionButton;
    ofxVec2Slider guiPos;
    ofxColorSlider guiColor;
    ofxIntSlider sadDegree;
    ofxLabel screenSize;
    ofxPanel gui;
    
    string timeString;
    string eventString;
    ofTrueTypeFont font;
   

};

class Element {
    
    public:
    Element(int x, int y){
        pos.x = x;
        pos.y = y;
        targetPos = pos;
        pct = 0;
        rZ=0;
    }
     
     ofVec3f initialPos;
     float r;
     float pct;
     float rZ;
     ofColor color;
     ofVec3f pos;
     void zenoToPoint(float catchUpSpeed);
     void interpolateByPct(int x1, int y1, int x2, int y2, float speed);
     void changeColor(Element object);
     void renderLeaf();
     void update();
     void moveTo(ofVec3f target, float speed);
    
     void appleMove();
     void appleStopMove();
     void renderApple();
     void renderElephant();
     void elephantMove();
     void rotate(float a);
     void stopRotate();
    
    private:
    ofVec3f targetPos ;
    
    
    void setTargetPos(int x, int y);
   
};

class Chameleon {
    
    public:
    Chameleon(){
      //  pos.x = x;
        //pos.y = y;
        targetPos = pos;
        
        foot_front = 23.0;
        foot_back = 2.0;
        dr = 1;
        r = 100;
    }
    
     
     ofVec3f initialPos;
     float r;
     float pct;
     ofVec3f pos;
     ofColor color;
    
    
    void zenoToPoint(int x, int y,float catchUpSpeed);
    void moveTo(ofVec3f target, float speed);
  
    void setCurrentPos(int x, int y);
    void changeColorByElement(Element object, float a);
    void changeColor(ofColor targetColor, float a);
    void render(int emotion);
    void update();
    void walk(float step);
    void renderReverse(int emotion);
    void render2(int emotion);
    void render3(int emotion);
   

    private:
    ofVec3f targetPos ;
    float foot_front;
    float foot_back;
    int dr;
    
    void setTargetPos(int x, int y);
    
};


