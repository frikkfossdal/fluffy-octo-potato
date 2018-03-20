#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   //cam.enableOrtho();
    cam.setDistance(100);
    //objectToSlice.incSlice();
    
    slicerSettings.setup();
    slicerSettings.setName("Slicer Control");
    slicerSettings.add(button.setup("slice"));
    slicerSettings.add(toggle.setup("showSlice",true));
    slicerSettings.add(objectToSlice.layerIndex);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(55);
    slicerSettings.draw();
    cam.begin();
    //ofDrawGrid();
    //objectToSlice.showModel();
    //objectToSlice.showDisco();
    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    index++;
    if(index >300){
        index = 0;
    }
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
