 #include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    conductor.setupGui();
}

//--------------------------------------------------------------
void ofApp::update(){
    conductor.parameterAdj();
    conductor.updateSlicer();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(55);
    conductor.drawAllGui();
    cam.begin();
    conductor.drawModel();
    conductor.drawPrinterBox();
    cam.end();
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
