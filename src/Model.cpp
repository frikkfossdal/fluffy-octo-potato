//
//  Model.cpp
//  slicer
//
//  Created by Frikk Fossdal on 19.02.2018.
//

#include "Model.hpp"

Model::Model(){
    threeDeeFile.loadModel("Body1.stl");
}
void Model::showModel(){
    ofSetLineWidth(1);
    ofSetColor(255);
    threeDeeFile.drawWireframe();
   
}
void Model::showDisco(int index){
     layers[index].show();
}

void Model::incSlice(){
    buildTriangles();
    sortTriangles();
    createLayers();
    std::vector<Triangles> activeTriangleList = triangleList;
    
    for(auto it = layers.begin(); it !=layers.end(); it++){
        activeTriangleList = it->checkTriangles(activeTriangleList); 
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
    //find zmax and zmin for all triangles
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

