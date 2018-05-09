//
//  Parameters.cpp
//  fluffy-octo-potato
//
//  Created by Frikk Fossdal on 09.05.2018.
//

#include "Parameters.hpp"
Parameters::Parameters(){
    layerHeight = 0.01;
}
void Parameters::setup(){
    slicerParameters.add(slice.set("slice", false));
    slicerParameters.add(layerHeight.set("layerHeight", 0.1, 0, 0.6));
    //Panel
    slicerControl.setup();
    slicerControl.setName("Slicer Control Panel");
    slicerControl.add(slice);
    slicerControl.add(layerHeight); 
}
void Parameters::drawSlicerControl(){
    slicerControl.draw();
}
