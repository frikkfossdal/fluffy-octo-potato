//
//  Model.cpp
//  slicer
//
//  Created by Frikk Fossdal on 19.02.2018.
//

#include "Model.hpp"

Model::Model(){
    threeDeeFile.loadModel("stress.stl");
    fixPosition();
    setup();
}
void Model::setup(){
    parameters.add(layerIndex.set("layer: ",0,0,1000));
    parameters.add(layerHeight.set("layerHeight: ", .1, 0, 1));
    parameters.add(drawTriangles.set("drawTriangles",false));
    parameters.add(drawWireFrame.set("drawWireFrame",true));
    parameters.add(drawSegments.set("drawSegments",false));
    parameters.add(drawContours.set("drawContours",false));
    parameters.add(slice.set("Start slicing", false));
    parameters.add(modelPosition.set("position", ofVec3f(0,0,0), ofVec3f(0,0,0), ofVec3f(400,400,50)));
}
void Model::update(){
    threeDeeFile.setPosition(modelPosition->x, modelPosition->y, modelPosition->z);
}
void Model::showModel(){
    ofSetLineWidth(1);
    ofSetColor(255,10);
    if(drawWireFrame == true){
        threeDeeFile.drawWireframe();
    }
//    Implement this when the UI is ready.
//    layers[layerIndex].show();
//    if(drawTriangles == true){
//        for(auto it = triangleList.begin(); it != triangleList.end(); it++){
//            it->show();
//        }
//    }
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
    //create vector containing all faces of mesh
    int meshIndex = 0;
    ofMesh mesh = threeDeeFile.getMesh(meshIndex);
    
    std::vector<ofMeshFace> faces = mesh.getUniqueFaces();
    //loop through the faces and create triangle objects
    int scl = 10;
    for(auto f = faces.begin(); f != faces.end(); f++){
        Triangles newTriangle(f->getVertex(0),f->getVertex(1), f->getVertex(2));
        
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
    layerIndex.set("layer: ", 0,0,numberOfLayers-1);
}
void Model::fixPosition(){
    //this needs to me modified to handle any "origin-point"
    ofVec3f sceneMax = threeDeeFile.getSceneMax();
    threeDeeFile.setScaleNormalization(false);
    ofVec3f center = threeDeeFile.getSceneCenter();
    //threeDeeFile.setPosition(center.x, center.y, 0);
}

