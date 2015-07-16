#pragma once

#include "ofMain.h"
#include "ofxOsc.h"


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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void readNewLine();
    ofFile pulse_file;
    int init_time;
    ofBuffer buff;
    int value;
    int pValue;
    int time;
    int shiftTime;
    int x;
    int threshold;
    int floor;
    float beatTime;
    
    ofxOscSender sender;

};
