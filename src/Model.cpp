//
//  Model.cpp
//  slicer
//
//  Created by Frikk Fossdal on 19.02.2018.
//

#include "Model.hpp"

Model::Model(){
    threeDeeFile.loadModel("Test1.stl");
    fixPosition();
    setup();
}
void Model::setup(){
    parameters.add(layerIndex.set("layer: ",1,0,1000));
    parameters.add(layerHeight.set("layerHeight: ", .1, 0, 1));
    parameters.add(drawTriangles.set("drawTriangles",false));
    parameters.add(drawWireFrame.set("drawWireFrame",true));
    parameters.add(drawSegments.set("drawSegments",false));
    parameters.add(drawContours.set("drawContours",false));
    parameters.add(slice.set("Start slicing", false));
    parameters.add(modelPosition.set("position", ofVec3f(0,0,0), ofVec3f(0,0,0), ofVec3f(400,400,50)));
    parameters.add(scl.set("Scale", 1, 0, 10));
    sliceFinish = false;
}
void Model::update(){
    threeDeeFile.setPosition(modelPosition->x, modelPosition->y, modelPosition->z);
    threeDeeFile.setScale(scl,scl,scl);
    
    //slice_button setup
    //add logic that destroys the existing sliced object. 
    if(slice == true){
        incSlice();
        slice = false;
    }
}
void Model::showModel(){
    ofSetLineWidth(1);
    ofSetColor(255,10);
    if(drawWireFrame == true){
        threeDeeFile.drawWireframe();
    }
    ofDrawRectangle(0, 0, 300, 300);
    if(layers.size() > 10)
    {
        layers[layerIndex].show();
        if(drawTriangles == true){
            for(auto it = triangleList.begin(); it != triangleList.end(); it++){
                it->show();
            }
        }
    }
}
void Model::incSlice(){
    //First, empty both triangleList and layerList
    triangleList.clear();
    layers.clear();
    
    //Then, do slice-calculation
    buildTriangles();
    createLayers();
    std::vector<Triangles> activeTriangleList;
    for(auto it = layers.begin(); it !=layers.end(); it++){
        it->calculate(triangleList);
    }
}

void Model::buildTriangles(){
    //create vector containing all faces of mesh
    int meshIndex = 0;
    ofMesh mesh = threeDeeFile.getMesh(meshIndex);
    
    std::vector<ofMeshFace> faces = mesh.getUniqueFaces();
    //loop through the faces and create triangle objects
    for(auto f = faces.begin(); f != faces.end(); f++){
        Triangles newTriangle(f->getVertex(0).operator+(threeDeeFile.getPosition()),f->getVertex(1).operator+(threeDeeFile.getPosition()), f->getVertex(2).operator+(threeDeeFile.getPosition()));
        
        triangleList.push_back(newTriangle);
    }
    //sort triangleList in terms of z-height
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
    int numberOfLayers = (layerMax-layerMin)/layerHeight;
    for(int i = 0; i < numberOfLayers; i++)
    {
        layers.push_back(Layer(layerHeight*i));
    }
    layerIndex.set("layer: ", 1,0,numberOfLayers-1);
    sliceFinish = true;
}
void Model::fixPosition(){
    //You have to errors.
    //1. The calculated triangles seems to be mirrored
    //2. The position of the calculated triangles is wrong
    ofVec3f sceneMax = threeDeeFile.getSceneMax();
    threeDeeFile.setScaleNormalization(false);
    threeDeeFile.enableNormals();
}

