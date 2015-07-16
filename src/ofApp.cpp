#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    pulse_file.open(ofToDataPath("pulse_data.txt"));
    buff = pulse_file.readToBuffer();
    
    string line = buff.getFirstLine();
    int i = line.find(" ");
    
    value = ofToInt(line.substr(1, i));
    init_time = ofToInt(line.substr(i));
    time = 0;
    shiftTime = ofGetElapsedTimeMillis();
    threshold = 350;
    floor = 250;
    
    string host = "localhost";
    int port = 8000;
    sender.setup(host, port);
    cout << "Sending to "<< host << " " << port << endl;
}

//--------------------------------------------------------------
void ofApp::update(){    int current = ofGetElapsedTimeMillis() - shiftTime;
    if(current >= time ){
        x = (x + 1) % ofGetWidth();
        readNewLine();
        ofxOscMessage m;
        m.setAddress("/heart");
        m.addIntArg(value - floor);
        sender.sendMessage(m);

        
        if(value > threshold && pValue < threshold){
            float ellapsed = ofGetElapsedTimeMillis() - beatTime;
            int bpm = int(60000 / ellapsed);
            if(bpm > 40 && bpm < 100){
                ofxOscMessage m;
                m.setAddress("/bpm");
                m.addIntArg(bpm);
                sender.sendMessage(m);
            }
            
            beatTime = ofGetElapsedTimeMillis();
        }
        pValue = value;
    }
    
}

void ofApp::readNewLine(){
    if(!buff.isLastLine()){
        string line = buff.getNextLine();
        int i = line.find(" ");
        value = ofToInt(line.substr(1, i));
        time  = ofToInt(line.substr(i)) - init_time;
    }
    else{
        buff.resetLineReader();
        string line = buff.getFirstLine();
        int i = line.find(" ");
        
        value = ofToInt(line.substr(1, i));
        time = ofToInt(line.substr(i))  - init_time;
        shiftTime = ofGetElapsedTimeMillis();

    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 0, 0);
    ofLine(x, ofGetHeight(), x, ofGetHeight() - value + floor);
    ofLine(0, threshold  + floor, ofGetWidth(), threshold  + floor);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
