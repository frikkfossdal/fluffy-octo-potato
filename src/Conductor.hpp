//
//  Conductor.hpp
//  fluffy-octo-potato
//
//  Created by Frikk Fossdal on 09.05.2018.
//

#ifndef Conductor_hpp
#define Conductor_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxSlicer.h"
#include "ofxGui.h"

class Conductor{
public:
    //constructor
    Conductor();
    
    //variables
    ofParameterGroup slicerParameters;
    ofParameterGroup simulatorParameters;
    ofParameter<float> layerHeight;
    ofParameter<float> scl;
    ofParameter<int> layerIndex;
    ofParameter<bool> drawSegments;
    ofParameter<bool> loadFile;
    ofParameter<bool> slice; 
    ofParameter<ofVec2f> pos;
    string filePath;
    string fileName;
    ofxPanel slicerControl;
    ofxSlicer slicerObj;
    
    //methods
    //---------------SETUP FUNCTIONS---------------
    //setup functions
    void setupGui();
    void setupSlicer();
    //---------------DRAW FUNCTIONS----------------
    void drawAllGui();
    void drawModel();
    void drawPrinterBox();
    void drawSlicedModel(); 
    
    //---------------UPDATE FUNCTIONS--------------
    void parameterAdj();
    void updateSlicer();
private:
    //---------------PRIVATE VARIABLES-------------
    ofVec2f prevPos;
    float prevScl;
    string prevFile;
    //---------------GERERAL FUNCTIONS-------------
    void getFile(ofFileDialogResult result);
    void updateGui(bool _sliceFinished);
};

#endif /* Conductor_hpp */
