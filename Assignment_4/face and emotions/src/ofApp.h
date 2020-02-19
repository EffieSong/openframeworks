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
    
    void drawApple();
     void drawMaple();
    void drawChameleon();
    void drawTree();
        
		void gotMessage(ofMessage msg);
    ofxPanel gui;
    ofParameter <int> uiMode;
    ofParameter <ofVec4f> uiPositionX;
    ofParameter <ofVec4f> uiPositionY;

};
