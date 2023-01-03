#include "geometry.hpp"

blimp::Geometry::Geometry() {

}

blimp::Geometry::Geometry(ColorVector* colors) {
    this -> setColors(colors);
}

GLfloat* blimp::Geometry::getVertices() {
    return this -> vertices;
}

GLfloat* blimp::Geometry::getColors() {
    return this -> colors;
}

void blimp::Geometry::setColors(ColorVector* colors) {
    //  allocate as much colors as there are vertices
    this -> colors = new GLfloat[this -> vertexCount * 4];
    int colorsSize = colors -> size();

    for (int i = 0; i < this -> vertexCount; i++) {
        this -> colors[i*4] = colors -> at((i*4) % colorsSize).getR();
        this -> colors[i*4+1] = colors -> at((i*4) % colorsSize).getG();
        this -> colors[i*4+2] = colors -> at((i*4) % colorsSize).getB();
        this -> colors[i*4+3] = colors -> at((i*4) % colorsSize).getA();
    }
}

GLfloat* blimp::Geometry::getNormals() {
    return this -> normals;
}

int blimp::Geometry::getVertexCount() {
    return this -> vertexCount;
}
