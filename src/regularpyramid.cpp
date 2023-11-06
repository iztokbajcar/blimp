#include <glm/glm.hpp>

#include "regularpolygon.hpp"
#include "regularpyramid.hpp"

blimp::RegularPyramid::RegularPyramid(int sides, float radius, float height, ColorVector* colors) {
    Geometry* base = new RegularPolygon(sides, radius, colors);

    int baseVertexCount = base -> getVertexCount();
    GLfloat* baseVertices = base -> getVertices();
    GLfloat* baseNormals = base -> getNormals();
    GLfloat* baseTexCoords = base -> getTexCoords();

    // invert the base normals
    for (int i = 0; i < baseVertexCount; i++) {
       baseNormals[i*3+2] *= -1;
    }

    this -> vertexCount = 
        baseVertexCount +  // base face
        sides * 3;  // 3 vertices (1 triangle) per side

    int firstSideVertexOffset = baseVertexCount;  // the index of the first coordinate of the first vertex of the first side in this -> vertices

    this -> vertices = new GLfloat[vertexCount*3];
    this -> normals = new GLfloat[vertexCount*3];
    this -> texCoords = new GLfloat[vertexCount*2];

    // construct the vertices
    // base
    for (int i = 0; i < baseVertexCount; i++) {
        this -> vertices[i*3] = baseVertices[i*3];
        this -> vertices[i*3+1] = baseVertices[i*3+1];
        this -> vertices[i*3+2] = baseVertices[i*3+2];

        this -> normals[i*3] = baseNormals[i*3];
        this -> normals[i*3+1] = baseNormals[i*3+1];
        this -> normals[i*3+2] = baseNormals[i*3+2];

        this -> texCoords[i*2] = baseTexCoords[i*2];
        this -> texCoords[i*2+1] = baseTexCoords[i*2+1];
    }

    glm::vec3 baseCenter = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 topVertex = glm::vec3(0.0f, 0.0f, height);

    // side faces
    for (int side = 0; side < sides; side++) {
        int vertex1Index = 1 + (side - 1) * 3;
        int vertex2Index = 2 + (side - 1) * 3;

        // if this is the first side, don't skip the first vertex
        if (side == 0) {
            vertex1Index = 0;
            vertex2Index = 1;
        }

        // the last side is between the last vertex and the first vertex
        // if this is the last side, An+1 is the first vertex
        if (side == sides - 1) {
            vertex1Index = 2 + (side - 2) * 3;
            vertex2Index = 0;
        }

        // coordinates of vertex `An` in base polygon
        GLfloat v0X = baseVertices[vertex1Index*3];
        GLfloat v0Y = baseVertices[vertex1Index*3+1];
        GLfloat v0Z = baseVertices[vertex1Index*3+2];

        // coordinates of vertex `An+1` in base polygon
        GLfloat v1X = baseVertices[vertex2Index*3];
        GLfloat v1Y = baseVertices[vertex2Index*3+1];
        GLfloat v1Z = baseVertices[vertex2Index*3+2];

        // normal
        glm::vec3 v0 = glm::vec3(v0X, v0Y, v0Z);
        glm::vec3 v1 = glm::vec3(v1X, v1Y, v1Z);
        glm::vec3 v0ToV1 = v1 - v0;
        glm::vec3 v0ToTop = topVertex - v0;
        glm::vec3 cross = glm::cross(v0ToV1, v0ToTop);
        glm::vec3 normal = glm::normalize(cross);

        int i = (firstSideVertexOffset + side * 3) * 3;
        int ti = (firstSideVertexOffset + side * 3) * 2;  // index in texCoords

        this -> vertices[i] = v0X;
        this -> vertices[i+1] = v0Y;
        this -> vertices[i+2] = v0Z;

        this -> vertices[i+3] = v1X;
        this -> vertices[i+4] = v1Y;
        this -> vertices[i+5] = v1Z;

        this -> vertices[i+6] = topVertex.x;
        this -> vertices[i+7] = topVertex.y;
        this -> vertices[i+8] = topVertex.z;

        for (int j = 0; j < 9; j += 3) {
            this -> normals[i+j] = normal.x;
            this -> normals[i+j+1] = normal.y;
            this -> normals[i+j+2] = normal.z;
        }

        this -> texCoords[ti] = 0;  // edge vertex 1 x
        this -> texCoords[ti+1] = 0;  // edge vertex 1 y

        this -> texCoords[ti+2] = 1;  // edge vertex 2 x
        this -> texCoords[ti+3] = 0;  // edge vertex 2 y

        this -> texCoords[ti+4] = 0.5;  // top vertex x
        this -> texCoords[ti+5] = 1;  // top vertex y
    }

    this -> setColors(colors);

    delete base;
}