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
    ofParameter<bool> slice;
    ofParameter<bool> drawTriangles;
    ofParameter<bool> drawSegments;
    ofParameter<bool> loadFile;
    ofParameter<int> slicerProgress; 
    string filePath;
    ofParameter<ofVec2f> pos;
    ofxPanel slicerControl; 
    
    ofxSlicer slicerObj;
    
    //methods
    //---------------SETUP FUNCTIONS---------------
    //setup functions
    void setupGui();
    void setupSlicer();
    //---------------DRAW FUNCTIONS----------------
    void drawAllGui();
    
    //---------------UPDATE FUNCTIONS--------------
    void updateGuiPar();
    void updateSlicer();
    
private:
    //---------------GERERAL FUNCTIONS-------------
    void getFile(ofFileDialogResult result);
};

#endif /* Conductor_hpp */
