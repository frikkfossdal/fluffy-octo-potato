 #include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //cam.enableOrtho();
    cam.setDistance(100);
    objectToSlice.incSlice();
    
    slicerSettings.setup();
    slicerSettings.setName("Slicer Control");
    slicerSettings.add(objectToSlice.layerIndex);
    slicerSettings.add(objectToSlice.drawTriangles);
    slicerSettings.add(objectToSlice.drawWireFrame);
    slicerSettings.add(objectToSlice.drawSegments);
    slicerSettings.add(objectToSlice.drawContours);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    //ofBackground(55);
    ofBackgroundGradient(ofColor(64), ofColor(55));
    slicerSettings.draw();
    cam.begin();
    objectToSlice.showModel();
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
