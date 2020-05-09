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
    
    void unixTime2Str(int n, char strTime[], int bufLen);
    
    ofxFloatSlider windSpeed;
    ofxFloatSlider temperature;
    ofxIntSlider daytime;
    ofxFloatSlider separateWeight;
    ofxFloatSlider cohesionWeight;
    ofxFloatSlider alignWeight;
    ofxFloatSlider flowWeight;
    ofxFloatSlider max_Force;
    ofxFloatSlider max_Speed;
    ofxPanel gui;
    
};


class FlowField{
public:
    FlowField(){
        resolution = 20;
        
    }
    int resolution ;
    int cols;
    int rows;
    ofVec3f **field;
    
    void flow();
    ofVec3f lookup(ofVec3f lookup);
    void displayLine();
};

class Boid {
    public:
    Boid(){
        pos = ofVec3f(0,0,0);
        acc = ofVec3f(0,0,0);
       // vel = ofVec3f(0,0,0);
        maxForce = 0.5;
        maxSpeed = 2.5;
       
    }
    ofVec3f getSeekSteer(ofVec3f target);
    ofVec3f getSeparateSteer(Boid *others, float radius);
    ofVec3f getAlignSteer(Boid *others);
    ofVec3f getCohesionSteer(Boid *others);
    void applyForce(ofVec3f f);
    void flock(Boid *boids, float separateWeight,float cohesionWeight,float alignWeight,float flowForce);
    void update();
    void render();
    ofVec3f flow(FlowField flowField);
    
    ofVec3f pos;
    ofVec3f acc;
    ofVec3f vel;
    float maxForce;
    float maxSpeed;
};
