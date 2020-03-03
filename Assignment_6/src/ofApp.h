#pragma once

#include "ofMain.h"

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
    
        void drawFbo(bool draw);
    
       

    ofTrueTypeFont font;
    string text;
};

class Element {
    
    public:
    Element(int x, int y){
        pos.x = x;
        pos.y = y;
        targetPos = pos;
        
    }
     ofVec3f pos;
     ofVec3f initialPos;
    float r;
     float pct;
     ofColor color;
    
     void zenoToPoint(float catchUpSpeed);
     void interpolateByPct(float speed);
     void setTargetPos(int x, int y);
     void changeColor(Element object);
     void renderChameleon();
     void renderLeaf();
    void update();
    
     
    
    private:
    ofVec3f targetPos ;

    

    
};

