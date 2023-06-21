#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>

#include "regularprism.hpp"
#include "regularpolygon.hpp"

blimp::RegularPrism::RegularPrism(int sides, float radius, float height, ColorVector* colors) {
    Geometry* base1 = new RegularPolygon(sides, radius, colors);
    Geometry* base2 = new RegularPolygon(sides, radius, colors);

    int baseVertexCount = base1 -> getVertexCount();  // should be equal to base2 -> getVertexCount()
    GLfloat* base1Vertices = base1 -> getVertices();
    GLfloat* base2Vertices = base2 -> getVertices();
    GLfloat* base1Normals = base1 -> getNormals();
    GLfloat* base2Normals = base2 -> getNormals();

    // add `height` to the z coordinates of the vertices of base2
    for (int i = 0; i < baseVertexCount; i++) {
       base2Vertices[i*3+2] += height;
       base1Normals[i*3+2] *= -1;  // invert the normals of base1
    }

    this -> vertexCount = 
        baseVertexCount * 2 +  // 2 bases
        sides * 6;  // 6 vertices (2 triangles) per side

    int firstSideVertexOffset = baseVertexCount * 2;  // the index of the first coordinate of the first vertex of the first side in this -> vertices

    this -> vertices = new GLfloat[vertexCount*3];
    this -> normals = new GLfloat[vertexCount*3];

    // construct the vertices
    // base 1
    for (int i = 0; i < baseVertexCount; i++) {
        this -> vertices[i*3] = base1Vertices[i*3];
        this -> vertices[i*3+1] = base1Vertices[i*3+1];
        this -> vertices[i*3+2] = base1Vertices[i*3+2];

        this -> normals[i*3] = base1Normals[i*3];
        this -> normals[i*3+1] = base1Normals[i*3+1];
        this -> normals[i*3+2] = base1Normals[i*3+2];
    }

    // base 2
    for (int i = 0; i < baseVertexCount; i++) {
        this -> vertices[(baseVertexCount+i)*3] = base2Vertices[i*3];
        this -> vertices[(baseVertexCount+i)*3+1] = base2Vertices[i*3+1];
        this -> vertices[(baseVertexCount+i)*3+2] = base2Vertices[i*3+2];

        this -> normals[(baseVertexCount+i)*3] = base2Normals[i*3];
        this -> normals[(baseVertexCount+i)*3+1] = base2Normals[i*3+1];
        this -> normals[(baseVertexCount+i)*3+2] = base2Normals[i*3+2];
    }

    glm::vec3 base1Center = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 base2Center = glm::vec3(0.0f, 0.0f, height);

    // sides
    // in the context of the base polygon, let side N be the side between vertices N and N+1
    for (int side = 0; side < sides; side++) {
        // vertices: [A1, A2, A3, A1, A3, A4, A1, A4, A5, ..., A1, An-1, An]
        // side 0: 0 1  (A1, A2)
        // side 1: 1 2  (A2, A3)
        // side 2: 4 5  (A3, A4)
        // side 3: 7 8  (A4, A5)
        // ...
        // side n-2: n-2 n-1  (An-1, An)
        // side n-1: n-1 n    (An, A1) 

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

        // coordinates of vertex `An` in base polygon 1
        GLfloat base1V0X = base1Vertices[vertex1Index*3];
        GLfloat base1V0Y = base1Vertices[vertex1Index*3+1];
        GLfloat base1V0Z = base1Vertices[vertex1Index*3+2];

        // coordinates of vertex `An+1` in base polygon 1
        GLfloat base1V1X = base1Vertices[vertex2Index*3];
        GLfloat base1V1Y = base1Vertices[vertex2Index*3+1];
        GLfloat base1V1Z = base1Vertices[vertex2Index*3+2];
        
        // coordinates of vertex `An` in base polygon 2
        GLfloat base2V0X = base2Vertices[vertex1Index*3];
        GLfloat base2V0Y = base2Vertices[vertex1Index*3+1];
        GLfloat base2V0Z = base2Vertices[vertex1Index*3+2];

        // coordinates of vertex `An+1` in base polygon 2
        GLfloat base2V1X = base2Vertices[vertex2Index*3];
        GLfloat base2V1Y = base2Vertices[vertex2Index*3+1];
        GLfloat base2V1Z = base2Vertices[vertex2Index*3+2];

        // normal
        glm::vec3 v0 = glm::vec3(base1V0X, base1V0Y, base1V0Z);
        glm::vec3 v1 = glm::vec3(base1V1X, base1V1Y, base1V1Z);
        glm::vec3 v0ToV1 = v1 - v0;
        glm::vec3 normal = glm::normalize((v0 + v0ToV1) - base1Center);

        int i = (firstSideVertexOffset + side*6)*3;

        // the first triangle of the side face
        // base 1 vertex 0, base 2 vertex 1, base 2 vertex 0
        this -> vertices[i] = base1V0X;     //  2V0     2V1 
        this -> vertices[i+1] = base1V0Y;   //   *-------*  
        this -> vertices[i+2] = base1V0Z;   //   |      /   
                                            //   |     /    
        this -> vertices[i+3] = base2V1X;   //   |    /     
        this -> vertices[i+4] = base2V1Y;   //   |   /      
        this -> vertices[i+5] = base2V1Z;   //   |  /       
                                            //   | /        
        this -> vertices[i+6] = base2V0X;   //   |/         
        this -> vertices[i+7] = base2V0Y;   //   *          
        this -> vertices[i+8] = base2V0Z;   //  1V0   

        this -> normals[i] = normal.x;
        this -> normals[i+1] = normal.y;
        this -> normals[i+2] = normal.z;
        this -> normals[i+3] = normal.x;
        this -> normals[i+4] = normal.y;
        this -> normals[i+5] = normal.z;
        this -> normals[i+6] = normal.x;
        this -> normals[i+7] = normal.y;
        this -> normals[i+8] = normal.z;      

        // the second triangle of the side face
        // base 1 vertex 0, base 1 vertex 1, base 2 vertex 1
        this -> vertices[i+9] = base1V0X;   //          2V1 
        this -> vertices[i+10] = base1V0Y;  //           *  
        this -> vertices[i+11] = base1V0Z;  //          /|   
                                            //         / |   
        this -> vertices[i+12] = base1V1X;  //        /  |   
        this -> vertices[i+13] = base1V1Y;  //       /   |   
        this -> vertices[i+14] = base1V1Z;  //      /    |   
                                            //     /     |   
        this -> vertices[i+15] = base2V1X;  //    /      |     
        this -> vertices[i+16] = base2V1Y;  //   *-------*   
        this -> vertices[i+17] = base2V1Z;  //  1V0     1V1    

        this -> normals[i+9] = normal.x;
        this -> normals[i+10] = normal.y;
        this -> normals[i+11] = normal.z;
        this -> normals[i+12] = normal.x;
        this -> normals[i+13] = normal.y;
        this -> normals[i+14] = normal.z;
        this -> normals[i+15] = normal.x;
        this -> normals[i+16] = normal.y;
        this -> normals[i+17] = normal.z;
    }

    delete base1;
    delete base2;
}