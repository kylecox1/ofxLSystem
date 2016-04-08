#include "ofxLSTube.h"

ofxLSTube::ofxLSTube(){
    
}

void ofxLSTube::generate(ofMesh& mesh, const ofxLSBranch branch, const int radius, const int scaledRadius){
    ofMatrix4x4 beginMatrix = branch.begin.getGlobalTransformMatrix();
    ofMatrix4x4 endMatrix = branch.end.getGlobalTransformMatrix();

    int first = mesh.getNumVertices();
    for (int i = 0; i < resolution; i++){
        // if it is the last face, close it where the first face
        // was started
        if(i == resolution -1){
            mesh.addIndex(first+(i*2));
            mesh.addIndex(first);
            mesh.addIndex(first+1);

            mesh.addIndex(first+1);
            mesh.addIndex(first+(i*2)+1);
            mesh.addIndex(first+(i*2));
        }else{
            mesh.addIndex(first+(i*2));
            mesh.addIndex(first+(i*2)+2);
            mesh.addIndex(first+(i*2)+3);

            mesh.addIndex(first+(i*2)+3);
            mesh.addIndex(first+(i*2)+1);
            mesh.addIndex(first+(i*2));
        }
    }
    
    for (int i = 0; i < resolution; i++){
        //calculate x and y component
        float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        ofVec3f circleBottom = ofVec3f(x, y, 0.0);
        ofVec3f directionBottom = (ofVec3f() + circleBottom).getNormalized();

        float xTop = scaledRadius * cosf(theta);
        float yTop = scaledRadius * sinf(theta);
        ofVec3f circleTop = ofVec3f(xTop, yTop, 0.0);
        ofVec3f directionTop = (ofVec3f() + circleTop).getNormalized();

        // bottom
        mesh.addVertex(circleBottom * beginMatrix);
        mesh.addNormal(directionBottom * beginMatrix.getRotate());
        //top
        mesh.addVertex(circleTop * endMatrix);
        mesh.addNormal(directionTop * endMatrix.getRotate());
    }
}
