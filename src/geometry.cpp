#include "geometry.hpp"
#include <iostream>

blimp::Geometry::Geometry() {

}

blimp::Geometry::Geometry(ColorVector* colors) {
    this -> setColors(colors);
}

blimp::Geometry::~Geometry() {
    delete[] this -> vertices;
    delete[] this -> colors;
    delete[] this -> normals;
    delete[] this -> texCoords;
}

GLfloat* blimp::Geometry::getVertices() {
    return this -> vertices;
}

GLfloat* blimp::Geometry::getColors() {
    return this -> colors;
}

void blimp::Geometry::setColors(ColorVector* colors) {
    // if colors are defined (not a null pointer), use the specified colors
    // otherwise use the default color
    //! @todo The color is sometimes wrong (maybe something is uninitialized?), fix this
    if (colors == nullptr) {
        ColorVector cv = ColorVector {Color()};  // default color
        colors = &cv;
    }

    // allocate as much colors as there are vertices
    this -> colors = new GLfloat[this -> vertexCount * 4];
    int colorsSize = colors -> size();

    for (int i = 0; i < this -> vertexCount; i++) {
        this -> colors[i*4] = colors -> at(i % colorsSize).getR();
        this -> colors[i*4+1] = colors -> at(i % colorsSize).getG();
        this -> colors[i*4+2] = colors -> at(i % colorsSize).getB();
        this -> colors[i*4+3] = colors -> at(i % colorsSize).getA();
    }
}

GLfloat* blimp::Geometry::getNormals() {
    return this -> normals;
}

GLfloat* blimp::Geometry::getTexCoords() {
    return this -> texCoords;
}

int blimp::Geometry::getVertexCount() {
    return this -> vertexCount;
}
