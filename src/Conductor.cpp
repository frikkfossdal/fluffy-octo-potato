//
//  Conductor.cpp
//  fluffy-octo-potato
//
//  Created by Frikk Fossdal on 09.05.2018.
//

#include "Conductor.hpp"

Conductor::Conductor(){
    
}
void Conductor::setupGui(){
    //setup slicer GUI parameters
    slicerParameters.add(loadFile.set("loadFile",false));
    slicerParameters.add(layerHeight.set("layer height", 0.1, 0, 0.8));
    slicerParameters.add(scl.set("scale",1,0,1));
    slicerParameters.add(pos.set("position", ofVec2f(0,0), ofVec2f(0,0), ofVec2f(500,500)));
    slicerParameters.add(layerIndex.set("layerIndex",1,1,100));
    slicerParameters.add(drawSegments.set("calc. segments", false));
    slicerParameters.add(slice.set("Slice", false));
    
    //setup slicer GUI panel
    slicerControl.setup();
    slicerControl.setName("Slicer Control");
    slicerControl.add(slicerParameters);
    
}
void Conductor::drawAllGui(){
    slicerControl.draw();
    ofSetColor(255);
    
    //--------------------MODEL INFO---------------------
    ofDrawBitmapString("MODEL INFO", ofGetWidth()-200, 20);
    ofDrawBitmapString("filename: " + fileName, ofGetWidth()-200, 40);
    ofDrawBitmapString("layer height: " + ofToString(layerHeight), ofGetWidth()-200, 60);
    ofDrawBitmapString("number of layers: " + ofToString(slicerObj.layers.size()) ,ofGetWidth() -200, 80);
    ofDrawBitmapString("number of triangles: " + ofToString(slicerObj.layers.size()) ,ofGetWidth() -200, 80);
    
    //--------------------LAYER INFO---------------------
    ofDrawBitmapString("LAYER INFO", ofGetWidth()-200, 120);
    ofDrawBitmapString("layer index : " + ofToString(layerIndex), ofGetWidth()-200, 140);
    ofDrawBitmapString("jobs on layer: " + ofToString("/"), ofGetWidth()-200, 160);
    
}
void Conductor::setupSlicer(){
    
}
void Conductor::updateGuiPar(){
    //layerHeight adj.
    float nearestLayHeig = floorf(layerHeight*10 +0.5)/10.0f;
    layerHeight = nearestLayHeig;
    //scl adj.
    float nearestScl = floorf(scl*10 + 0.5)/10.0f;
    scl = nearestScl;
    
    //toggle slice
    if(slice==true){
        slicerObj.slice();
        slice = false;
        //update layerIndex
        slicerParameters.add(layerIndex.set("layerIndex",1,1,slicerObj.layers.size()-1));
    }
    if(loadFile == true){
        ofFileDialogResult result = ofSystemLoadDialog("Load file");
        //Check if the user opened a file
        if (result.bSuccess){
            ofLogVerbose("User selected a file");
            //We have a file, check it and process it
            getFile(result);
            
        }else {
            ofLogVerbose("User hit cancel");
        }
        loadFile = false;
    }
}
void Conductor::updateSlicer(){
    slicerObj.model.setPosition(pos->x, pos->y, 0);
    slicerObj.model.setScale(scl, scl, scl);
}
void Conductor::drawModel(){
    ofSetColor(255);
    slicerObj.showAssimpModel();
    ofNoFill();
    ofDrawBox(ofPoint(0,0,150), 600, 300, 300);
    ofPoint center = slicerObj.model.getSceneCenter(); 
    if(slicerObj.layers.size() > 10){   
    slicerObj.showSegments(layerIndex);
    }
}
//-------------------PRIVATE FUNCTIONS-----------------------------
//checks if the file is a stl
void Conductor::getFile(ofFileDialogResult result){
    string name = result.getName();
    string path = result.getPath();
    filePath = path;
    
    ofFile file (result.getPath());
    string fileExtension = ofToUpper(file.getExtension());
    //check if extension is .stl
    if(fileExtension == "STL")
    {
        slicerObj.loadFile(filePath);
        fileName = ofToString(file.getFileName());
    }
}

