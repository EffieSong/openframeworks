#include "ofApp.h"
#include "ofxJSON.h"

#include <time.h>
using namespace std;
ofxJSONElement root;
Boid* boids = new Boid[1000];
FlowField flowField;
float x = 0;
ofPolyline line;
//--------------------------------------------------------------
void ofApp::setup(){

    std::string url = "https://api.darksky.net/forecast/cab7cd7ec04039dd7337f1682c7202b3/39.9042,116.4074";

    // Now parse the JSON
    bool parsingSuccessful = root.open(url);

    if (parsingSuccessful)
    {
        ofLogNotice("ofApp::setup") << root.getRawString(true);
    } else {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON.";
    }
   
    int sunriseTime = root["daily"]["data"][0]["sunriseTime"].asInt();
    int sunsetTime = root["daily"]["data"][0]["sunsetTime"].asInt();
     gui.setup();

  gui.add(windSpeed.setup("WindSpeed",root["currently"]["windSpeed"].asFloat(),0.0,15.0));

  gui.add(temperature.setup("Temperature",root["currently"]["temperature"].asFloat(),0.0,100.0));
    
    gui.add(daytime.setup("dayTime",sunriseTime,sunriseTime,sunsetTime));
//    gui.add(cohesionWeight.setup("cohesion",1.1,0.0,10.0));
//    gui.add(alignWeight.setup("align",1.0,0.0,5.0));
//    gui.add(max_Force.setup("max_Force",0.01,0.0,0.03));
//    gui.add(max_Speed.setup("max_Speed",2.45,0.0,10.0));
//    gui.add(flowWeight.setup("flowWeight",5.8,0.0,10.0));
    cohesionWeight = 1.1f;
    alignWeight = 1.0f;
    max_Force = 0.011f;
    max_Speed = 2.45f;
    flowWeight = 5.8f;
    
    
    for(int i=0;i<300;i++){
        boids[i] = Boid();
        boids[i].pos = ofVec3f(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
        boids[i].vel = ofVec3f(0.5,0,0);
    }
    
    flowField.cols = ofGetWidth()/flowField.resolution;
    flowField.rows = ofGetHeight()/flowField.resolution;
    flowField.field = new ofVec3f*[flowField.cols];
    for(int i = 0;i<flowField.cols;i++){
        flowField.field[i] = new ofVec3f[flowField.rows];
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    flowField.flow();
    ofVec3f wind = ofVec3f(-1.0,0,0);
    wind.limit(max_Force);
    for(int i=0;i<1000;i++){
        boids[i].maxForce = max_Force;
        boids[i].maxSpeed = max_Speed;
        boids[i].flock(boids,ofMap(temperature,0.0f,100.0f,0.0f,18.0f), cohesionWeight,alignWeight,flowWeight);
       boids[i].vel += wind * windSpeed;
      }
}
std::ostringstream text;
float lerpTemp;

//--------------------------------------------------------------
void ofApp::draw(){

    std::string summary = root["currently"]["summary"].asString();
    time_t sunriseTime = root["daily"]["data"][0]["sunriseTime"].asInt();
    int sunsetTime = root["daily"]["data"][0]["sunsetTime"].asInt();
    time_t currentEpoch = root["currently"]["time"].asInt(); // get sample epoch
    float temp = root["currently"]["temperature"].asFloat();
    float wind = root["currently"]["windSpeed"].asFloat();
    time_t current = time(NULL);  // get current epoch

    

     struct tm* currentTime = localtime(&sunriseTime);
     char usrdefFormat[50] = { 0 };
     strftime(usrdefFormat, 50, "%Y-%m-%d %H:%M:%S", currentTime);


    
    if (ofGetFrameNum() == 1) {
      text << summary <<"\n"<< "Current epoch: " << currentEpoch <<"\n"<< "Sunrise time:" << sunriseTime <<"\n"<<"Sunset time: " << sunsetTime <<"\n"<< "Temperature: " << temp << "\n"<<"WindSpeed:"<<wind<<"\n"<<"Current time:"<<usrdefFormat;
     
       
    }
     ofSetColor(255,255,255);
    ofDrawBitmapString(text.str(), 20, 40);
    
    
    //Use sunrise/sunset time to change the background color.
   
     ofColor c(68, 169, 255); // Bright blue ...
       c.setBrightness(ofMap(daytime,sunriseTime,sunsetTime,255,20));
  

  
 ofSetBackgroundColor(c); // greenish
    
//temperature controls the color of circle
    ofColor tempColor;
    tempColor.setHex(0xb5dfff);
    ofColor highTem;
    highTem.setHex(0xfcba03);
    tempColor.lerp(highTem,  ofMap(temperature, 0.0, 100.0, 0.0, 1.0));
    ofSetColor(tempColor);
    
//wind speed controls the movement
    x+= windSpeed;
    if(x>ofGetWidth()){
        x=0.0;
    }
   
    
    
    gui.draw();
    cout<<temp<<lerpTemp<<endl;
     for(int i=0;i<300;i++){
         boids[i].render();
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


void ofApp::unixTime2Str(int n, char strTime[], int bufLen)
{
    struct tm tm = *localtime((time_t *)&n);
    strftime(strTime, bufLen - 1, "%Y-%m-%d %H:%M:%S", &tm);
    strTime[bufLen - 1] = '\0';
}

ofVec3f Boid::getSeekSteer(ofVec3f target){
    ofVec3f desired = (target-pos).getNormalized()*maxSpeed;
    ofVec3f steer = desired - vel;
    steer.limit(maxForce);
    return steer;
}

ofVec3f Boid::getSeparateSteer(Boid *others, float radius){
    float neighborDist = radius;
    ofVec3f sumDesired;
    ofVec3f steer;
    int count = 0;
    for(int i = 0; i< sizeof(*others)-1;i++){
        float d = pos.distance(others[i].pos);
        if(d>0 && d < neighborDist){
            ofVec3f diff = (pos - others[i].pos).getNormalized();
            diff /= d;
            sumDesired += diff;
            count++;
        }
    }
    if(count>0){
        sumDesired /= count;
        sumDesired = sumDesired.getNormalized()*maxSpeed;
        steer = sumDesired - vel;
        steer.limit(maxForce);
    }
    return steer;
    
}
ofVec3f Boid::getAlignSteer(Boid *others){
    float neighborDist = 50.0;
    ofVec3f sumDesired;
    ofVec3f steer;
    int count = 0;
    for(int i = 0; i< sizeof(*others)-1;i++){
        float d = pos.distance(others[i].pos);
        if(d>0 && d < neighborDist){
            sumDesired += others[i].vel;
            count++;
        }
    }
    if(count>0){
        sumDesired /= count;
        sumDesired = sumDesired.getNormalized()*maxSpeed;
        steer = sumDesired - vel;
        steer.limit(maxForce);
    }
    return steer;
    
}
ofVec3f Boid::getCohesionSteer(Boid *others){
    float neighborDist = 60;
    ofVec3f sumDesired;
    ofVec3f sumPos;
    ofVec3f steer;
    int count = 0;
    for(int i = 0; i< sizeof(others[0])-1;i++){
        float d = pos.distance(others[i].pos);
        if(d>0 && d < neighborDist){
            sumPos += others[i].pos;
            count++;
        }
    }
    if(count>0){
        sumDesired = (sumPos/count-pos).getNormalized()*maxSpeed;
        steer = sumDesired - vel;
        steer.limit(maxForce);
    }
    return steer;
}
void Boid::applyForce(ofVec3f f){
    acc += f;
}

void Boid::flock(Boid *boids,  float separateWeight,float cohesionWeight,float alignWeight,float flowForce){
  
    applyForce(getSeparateSteer(boids,150)*separateWeight);
    applyForce(getCohesionSteer(boids)*cohesionWeight);
    applyForce(getAlignSteer(boids)*alignWeight);
    applyForce(flow(flowField)*flowForce);
    

}

ofVec3f Boid::flow(FlowField flowField){
    ofVec3f desired = flowField.lookup(pos).getNormalized()*maxSpeed;
    ofVec3f steer = (desired - vel).limit(maxForce);
    return steer;
    
}

void Boid::update(){
    vel += acc;
    pos += vel;
   
    if(pos.x<0 || pos.y<0 || pos.y>ofGetHeight()){
        pos.x = ofRandom(ofGetWidth(),ofGetWidth()+20);
        pos.y = ofRandom(ofGetHeight());
    }
     acc.set(0,0,0);
}
void Boid::render(){
    update();
   
    ofPushMatrix();
        ofTranslate(pos.x, pos.y);
        ofVec3f v = vel.getNormalized()*30;
        ofVec3f v1 = vel.getNormalized()*10;
        ofVec3f v2 = vel.getNormalized()*10;
        v1.rotate(90, ofVec3f(0,0,1));
        v2.rotate(-90, ofVec3f(0,0,1));
    ofNoFill();
        ofBeginShape();
            ofVertex(ofVec3f(v.x, v.y,0));
            ofVertex(ofVec3f(v1.x, v1.y,0));
            ofVertex(ofVec3f(v2.x, v2.y,0));
        ofEndShape(true);
    ofPopMatrix();
 
}

void FlowField::flow(){
    float xoff = 0;
    for(int i = 0; i< cols; i++){
        float yoff = 0;
        for(int j = 0; j< rows; j++){
            float theta = ofMap(ofNoise(xoff, yoff,ofGetFrameNum()/400.0), 0, 1, 0, 2*PI);
            field[i][j] =ofVec3f(cos(theta),sin(theta));
            yoff += 0.05;
        }
        xoff += 0.05;
    }
}

ofVec3f FlowField::lookup(ofVec3f lookup){
    int column = ofClamp(lookup.x/resolution, 0, cols-1);
    int row = ofClamp(lookup.y/resolution, 0, rows-1);
    return field[column][row];
}

