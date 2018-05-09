//
//  Parameters.hpp
//  fluffy-octo-potato
//
//  Created by Frikk Fossdal on 09.05.2018.
//

#ifndef Parameters_hpp
#define Parameters_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
class Parameters{
public:
    //constructor
    Parameters();
    //methods
    void setup();
    void drawSlicerControl();
    //variables
    ofParameterGroup slicerParameters;
    ofParameter<bool> slice;
    ofParameter<float> layerHeight;
    //----------------------------------
    ofxPanel slicerControl; 
};

#endif /* Parameters_hpp */
