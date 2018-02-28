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
    float layerHeight;
    std::vector<Triangles> triangleList;
    std::vector<Layer> layers;
    float layerMax;
    float layerMin;
    ofParameter<int> layerIndex;
    ofParameterGroup parameters;

    //Constructors
    Model();
    
    //Methods
    void setup(); 
    void slice();
    void constructContour();
    void showModel();
    void showDisco(); 
    void incSlice();
    
private:
    //Create the input triangle list and sort it according to layerheights
    void buildTriangles(); //step3
    void sortTriangles();
    void findPerim();
    void createLayers();
};

#endif /* Model_hpp */
