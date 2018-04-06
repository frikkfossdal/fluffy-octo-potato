//
//  Model.hpp
//  slicer
//
//  Created by Frikk Fossdal on 19.02.2018.
//

#ifndef Model_hpp
#define Model_hpp
#include "ofxAssimpModelLoader.h"
#include "Triangles.hpp"
#include "Layer.hpp"
#include <stdio.h>

class Model : public ofThread {
public:
    //Variables;
    ofxAssimpModelLoader threeDeeFile;
    int numberOfLayers; 
    std::vector<Triangles> triangleList;
    std::vector<Layer> layers;
    float layerMax;
    float layerMin;
    //Model controls
    ofParameter<int> layerIndex;
    ofParameter<ofVec3f> modelPosition;
    ofParameter<bool> drawWireFrame;
    ofParameter<bool> drawSegments;
    ofParameter<bool> drawContours;
    ofParameter<bool> slice;
    ofParameter<bool> drawTriangles;
    ofParameter<float> layerHeight;
    ofParameter<float> scl;
    bool sliceFinish; 

    
    ofParameterGroup parameters;
    //Constructors
    Model();
    
    //Methods
    void setup();
    void update();
    void incSlice();
    void constructContour();
    void showModel();

private:
    //Create the input triangle list and sort it according to layerheights
    void buildTriangles(); //step3
    void sortTriangles();
    void findPerim();
    void createLayers();
    void fixPosition(); 
};

#endif /* Model_hpp */
