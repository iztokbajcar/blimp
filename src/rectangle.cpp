#include "rectangle.hpp"

blimp::Rectangle::Rectangle(float a, float b, ColorVector* colors) {
    this -> vertexCount = 6;  // 2 triangles
    this -> vertices = new GLfloat[6*3] {
        -a/2, -b/2,  0,  // front bottom left
         a/2, -b/2,  0,  // front bottom right
        -a/2,  b/2,  0,  // front top left

         a/2, -b/2,  0,  // front bottom right
         a/2,  b/2,  0,  // front top right
        -a/2,  b/2,  0,  // front top left
    };

    this -> normals = new GLfloat[6*3] {
         0,  0, -1,  // front bottom left  
         0,  0, -1,  // front bottom right
         0,  0, -1,  // front top left

         0,  0, -1,  // front bottom right
         0,  0, -1,  // front top right
         0,  0, -1,  // front top left
    };

    this -> texCoords = new GLfloat[6*2];
    // bottom left
    this -> texCoords[0] = 0;
    this -> texCoords[1] = 0;

    // bottom right
    this -> texCoords[2] = 1;
    this -> texCoords[3] = 0;

    // top left
    this -> texCoords[4] = 0;
    this -> texCoords[5] = 1;

    // bottom right
    this -> texCoords[6] = 1;
    this -> texCoords[7] = 0;

    // top right
    this -> texCoords[8] = 1;
    this -> texCoords[9] = 1;

    // top left
    this -> texCoords[10] = 0;
    this -> texCoords[11] = 1;

    this -> setColors(colors);
}  