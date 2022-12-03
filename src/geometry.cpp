#include "geometry.hpp"

blimp::Geometry::Geometry() {

}

GLfloat* blimp::Geometry::getVertices() {
    return this -> vertices;
}

int blimp::Geometry::getVertexCount() {
    return this -> vertexCount;
}