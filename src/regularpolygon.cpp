#include "regularpolygon.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <stdexcept>

blimp::RegularPolygon::RegularPolygon(int sides, float radius, ColorVector* colors) {
    if (sides < 3) {
        throw std::invalid_argument("A polygon must have at least 3 sides.");
    }

    int numOfDiagonals = sides - 3;  // number of diagonals between a vertex and all others, excluding sides
    float angle = glm::radians(360.0f / sides);  // angle between each vertex

    // construct the vertices of the polyogn
    GLfloat* polygonVertices = new GLfloat[sides*3];
    for (int i = 0; i < sides * 3; i += 3) {
        polygonVertices[i] = radius * cos(angle * (i / 3));      // x
        polygonVertices[i+1] = radius * sin(angle * (i / 3));    // y
        polygonVertices[i+2] = 0.0f;                             // z
    }

    GLfloat* polygonNormals = new GLfloat[sides*3];
    for (int i = 0; i < sides * 3; i += 3) {
        polygonNormals[i] = 0.0f;                                // x
        polygonNormals[i+1] = 0.0f;                              // y
        polygonNormals[i+2] = 1.0f;                              // z
    }

    this -> vertexCount = sides + (numOfDiagonals * 2); 
    this -> vertices = new GLfloat[vertexCount*3];
    this -> normals = new GLfloat[vertexCount*3];

    // construct the triangles
    // (0, 1, 2,    0, 2, 3,    0, 3, 4,    ...)
    int lastVertex = 1;
    for (int i = 0; i < vertexCount; i++) {
        switch (i % 3) {
            case 0:
                this -> vertices[i*3] = polygonVertices[0];
                this -> vertices[i*3+1] = polygonVertices[0+1];
                this -> vertices[i*3+2] = polygonVertices[0+2];
                this -> normals[i*3] = polygonNormals[0];
                this -> normals[i*3+1] = polygonNormals[0+1];
                this -> normals[i*3+2] = polygonNormals[0+2];
                break;
            case 1:
                this -> vertices[i*3] = polygonVertices[lastVertex*3];
                this -> vertices[i*3+1] = polygonVertices[lastVertex*3+1];
                this -> vertices[i*3+2] = polygonVertices[lastVertex*3+2];
                this -> normals[i*3] = polygonNormals[lastVertex*3];
                this -> normals[i*3+1] = polygonNormals[lastVertex*3+1];
                this -> normals[i*3+2] = polygonNormals[lastVertex*3+2];
                break;
            case 2:
                lastVertex++;
                this -> vertices[i*3] = polygonVertices[lastVertex*3];
                this -> vertices[i*3+1] = polygonVertices[lastVertex*3+1];
                this -> vertices[i*3+2] = polygonVertices[lastVertex*3+2];
                this -> normals[i*3] = polygonNormals[lastVertex*3];
                this -> normals[i*3+1] = polygonNormals[lastVertex*3+1];
                this -> normals[i*3+2] = polygonNormals[lastVertex*3+2];
                break;
        }
    }

    if (colors != nullptr) {
        this -> setColors(colors);
    } else {
        ColorVector cv = ColorVector {Color()};  // default color
        this -> setColors(&cv);
    }

    delete[] polygonVertices;
    delete[] polygonNormals;
}