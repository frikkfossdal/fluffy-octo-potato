 #include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setTarget(ofVec3f(300, 300));
    slicer.loadFile("rack.stl");
}

//--------------------------------------------------------------
void ofApp::update(){

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(55);
    ofNoFill();
    ofSetColor(255, 55);
    cam.begin();
    ofDrawRectangle(0, 0, 600, 600);
    slicer.showAssimpModel();
    cam.end();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    slicer.slice(); 
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
