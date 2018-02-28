//
//  Model.cpp
//  slicer
//
//  Created by Frikk Fossdal on 19.02.2018.
//

#include "Model.hpp"

Model::Model(){
    threeDeeFile.loadModel("Rack.stl");
    //
    fixPosition();
    setup();
}
void Model::setup(){
    parameters.add(layerIndex.set("layer: ",0,0,400));
    
}
void Model::showModel(){
    ofSetLineWidth(1);
    ofSetColor(255,10);
    threeDeeFile.drawWireframe();
}
void Model::showDisco(){
     layers[layerIndex].show();
}

void Model::incSlice(){
    //1. Build triangle-list
    buildTriangles();
    //2. Create layers
    createLayers();
    //3. Loop trough all layers and slice the triangles
    //First, decide where to control the active triangles. This is key if you fant your slicing to be fast.
    
    std::vector<Triangles> activeTriangleList;
    for(auto it = layers.begin(); it !=layers.end(); it++){
        //two steps
        //1. add relevant triangles to active triangles. Delete if processing is finished
        //2. calculate all triangle intersections
        //activeTriangleList = it->checkTriangles(activeTriangleList);
        it->calculate(triangleList);
    }
}
void Model::buildTriangles(){
    int meshIndex = 0;
    ofMatrix4x4 modelMatrix = threeDeeFile.getModelMatrix();
    ofMatrix4x4 meshMatrix = threeDeeFile.getMeshHelper(meshIndex).matrix;
    ofMatrix4x4 concatMatrix;
    concatMatrix.preMult(modelMatrix);
    concatMatrix.preMult(meshMatrix);
    
    ofMesh mesh = threeDeeFile.getMesh(meshIndex);
    int loopIndex = 0;
    int triIndex = 0;
    std::vector<ofVec3f> triBuffer;
    
    for(int i=0; i<mesh.getNumVertices(); i++) {
        ofVec3f & vert = mesh.getVertices()[i];
        vert.set(concatMatrix.preMult(vert));
        triBuffer.push_back(vert);
        //build a triangle object
        if(loopIndex == 2){
            loopIndex = 0;
            triangleList.push_back(Triangles(triBuffer[0], triBuffer[1], triBuffer[2]));
            triBuffer.clear();
        }
        else
        {
        loopIndex++;
        }
    }
    //Sort all triangles
    sortTriangles();
}
struct compareVector{
    bool operator()(Triangles &a, Triangles &b)
    {
        if(a.zMin < b.zMin){
            return true;
        }
        else{
            return false;
        }
    }
};
void Model::sortTriangles(){
    std::sort (triangleList.begin(), triangleList.end(), compareVector());
    findPerim(); 
}
void Model::findPerim(){
    Triangles lastTriangle = triangleList.back();
    Triangles firstTriangle = triangleList.front();
    layerMax = lastTriangle.zMax;
    layerMin = firstTriangle.zMin;
}
void Model::createLayers(){
    layerHeight = 0.1;
    int numberOfLayers = (layerMax-layerMin)/layerHeight;
    for(int i = 0; i < numberOfLayers; i++)
    {
        layers.push_back(Layer(layerHeight*i));
    }
}
void Model::fixPosition(){
    //this needs to me modified to handle any "origin-point"
    ofVec3f sceneMax = threeDeeFile.getSceneMax();
    threeDeeFile.setScaleNormalization(false);
    ofVec3f center = threeDeeFile.getSceneCenter();
    threeDeeFile.setPosition(center.x, center.y, 0);
}

