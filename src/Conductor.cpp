//
//  Conductor.cpp
//  fluffy-octo-potato
//
//  Created by Frikk Fossdal on 09.05.2018.
//
//TODO:
//1. Fix threading start and stop. You are fucking close --> still not happy with this. Keep experimenting
//2. Fix the structure of the conductor. Slice, then draw. Repeat.
//2. Only visualize layers when slicing is finished. 
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
    slicerParameters.add(layerIndex.set("layerIndex",1,1,1000));
    slicerParameters.add(slice.set("start slicing", false));
    
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
    
    //--------------------SLICER INFO---------------------
    ofDrawBitmapString("SLICER INFO", ofGetWidth()-200, 120);
    if(slicerObj.isActive==false){
        ofDrawBitmapString("slicer status: inactive", ofGetWidth()-200, 140);
    }
    if(slicerObj.isActive==true){
        ofDrawBitmapString("slicer status: slicing", ofGetWidth()-200, 140);
    }
    
    //--------------------LAYER INFO---------------------
    ofDrawBitmapString("LAYER INFO", ofGetWidth()-200, 180);
    ofDrawBitmapString("layer index : " + ofToString(layerIndex), ofGetWidth()-200, 200);
    ofDrawBitmapString("jobs on layer: 9", ofGetWidth()-200, 220);
    ofDrawBitmapString("layer time: 276s" , ofGetWidth()-200, 240);
}
void Conductor::setupSlicer(){
    
}
void Conductor::parameterAdj(){
    //layerHeight adj.
    float nearestLayHeig = floorf(layerHeight*10 +0.5)/10.0f;
    layerHeight = nearestLayHeig;
    //scl adj.
    float nearestScl = floorf(scl*10 + 0.5)/10.0f;
    scl = nearestScl;
    //pos adj.
    ofVec2f nearestPos = ofVec2f(floorf(pos->x*10 + 0.5)/10.0f,floorf(pos->y*10 + 0.5)/10.0f);
    pos = nearestPos;

}
void Conductor::updateSlicer(){
    //---------------LOAD FILE-------------
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
    //---------------CONTROL THE SLICER-------------
    //check if slicer has a model to work with
    if(slicerObj.hasModel == true)
    {
        //check if some of the parameters has changed.
        if(prevPos != pos || prevScl !=scl || prevFile != filePath){
            slicerObj.model.setScale(scl, scl, scl);
            slicerObj.model.setPosition(pos->x, pos->y, 0);
            std::cout << "parameter changed" << endl;
        }
        //preliminary slicer activation
        if(slice == true)
        {
            slice = false;
            slicerObj.startSlice();
        }
        prevPos = pos; 
        prevScl = scl;
    }
}
void Conductor::drawModel(){
    if(slicerObj.hasModel == true)
    {
        slicerObj.showAssimpModel();
    }
}
void Conductor::drawPrinterBox(){
    ofNoFill();
    ofSetColor(255,15);
    ofDrawBox(0, 0, 150, 300, 600, 300);
}
void Conductor::drawSlicedModel(){
    if(slicerObj.sliceFinished == true)
    {
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
        prevFile = filePath;
    }
}

