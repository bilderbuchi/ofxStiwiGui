#include "testApp.h"
#include "gui.h"

//--------------------------------------------------------------
void testApp::setup(){
}

//--------------------------------------------------------------
void testApp::update(){
	// update scope
	float* rand = new float[50];
	for(int i=0 ;i<50; i++){
		rand[i] = ofRandom(-1.0,1);
		
	}

	gui->update(scope, kofxGui_Set_FloatArray, rand, sizeof(float*));

	// make 3 seconds loop
	float f = ((ofGetElapsedTimeMillis()%3000) / 3000.0);
	gui->update(points, kofxGui_Set_Float, &f, sizeof(float));
}
void testApp::draw(){
	ofBackground(bkg,bkg,bkg);

	ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth()-50, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

		
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){


}


//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}



