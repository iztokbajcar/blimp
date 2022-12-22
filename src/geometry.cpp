#include "geometry.hpp"

blimp::Geometry::Geometry() {

}

GLfloat* blimp::Geometry::getVertices() {
    return this -> vertices;
}

GLfloat* blimp::Geometry::getColors() {
    return this -> colors;
}

int blimp::Geometry::getVertexCount() {
    return this -> vertexCount;
}