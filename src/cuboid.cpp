# include <glm/glm.hpp>

#include "cuboid.hpp"

blimp::Cuboid::Cuboid(float a, float b, float c, ColorVector* colors) {
    /* 
        A cuboid of the specified dimensions, centered at the origin.

            +----------------+
           /                /|
          +----------------+ |
          |              b | /
          |                |/ c
          +----------------+
                        a
    */

    this -> vertexCount = 12*3;  // 12 triangles, 3 vertices each
    this -> vertices = new GLfloat[12*3*3] {
        // front face
        -a/2, -b/2, -c/2,  // front bottom left  
         a/2, -b/2, -c/2,  // front bottom right
        -a/2,  b/2, -c/2,  // front top left

         a/2, -b/2, -c/2,  // front bottom right
         a/2,  b/2, -c/2,  // front top right
        -a/2,  b/2, -c/2,  // front top left

        // rear face
        -a/2, -b/2,  c/2,  // rear bottom left
         a/2, -b/2,  c/2,  // rear bottom right
        -a/2,  b/2,  c/2,  // rear top left

         a/2, -b/2,  c/2,  // rear bottom right
         a/2,  b/2,  c/2,  // rear top right
        -a/2,  b/2,  c/2,  // rear top left

        // top face
        -a/2,  b/2, -c/2,  // front top left
         a/2,  b/2, -c/2,  // front top right
        -a/2,  b/2,  c/2,  // rear top left

         a/2,  b/2, -c/2,  // front top right
         a/2,  b/2,  c/2,  // rear top right
        -a/2,  b/2,  c/2,  // rear top left

        // bottom face
        -a/2, -b/2, -c/2,  // front bottom left  
         a/2, -b/2, -c/2,  // front bottom right
        -a/2, -b/2,  c/2,  // rear bottom left

         a/2, -b/2, -c/2,  // front bottom right
         a/2, -b/2,  c/2,  // rear bottom right
        -a/2, -b/2,  c/2,  // rear bottom left

        // left face
        -a/2, -b/2, -c/2,  // front bottom left  
        -a/2, -b/2,  c/2,  // rear bottom left
        -a/2,  b/2, -c/2,  // front top left

        -a/2, -b/2,  c/2,  // rear bottom left
        -a/2,  b/2,  c/2,  // rear top left
        -a/2,  b/2, -c/2,  // front top left

        // right face
         a/2, -b/2, -c/2,  // front bottom right
         a/2, -b/2,  c/2,  // rear bottom right
         a/2,  b/2, -c/2,  // front top right

         a/2, -b/2,  c/2,  // rear bottom right
         a/2,  b/2,  c/2,  // rear top right
         a/2,  b/2, -c/2,  // front top right
    };

    this -> normals = new GLfloat[12*3*3] {
        // front face
         0,  0, -1,  // front bottom left  
         0,  0, -1,  // front bottom right
         0,  0, -1,  // front top left

         0,  0, -1,  // front bottom right
         0,  0, -1,  // front top right
         0,  0, -1,  // front top left

        // rear face
         0,  0,  1,  // rear bottom left
         0,  0,  1,  // rear bottom right
         0,  0,  1,  // rear top left

         0,  0,  1,  // rear bottom right
         0,  0,  1,  // rear top right
         0,  0,  1,  // rear top left

        // top face
         0,  1,  0,  // front top left
         0,  1,  0,  // front top right
         0,  1,  0,  // rear top left

         0,  1,  0,  // front top right
         0,  1,  0,  // rear top right
         0,  1,  0,  // rear top left

        // bottom face
         0, -1,  0,  // front bottom left  
         0, -1,  0,  // front bottom right
         0, -1,  0,  // rear bottom left

         0, -1,  0,  // front bottom right
         0, -1,  0,  // rear bottom right
         0, -1,  0,  // rear bottom left

        // left face
        -1,  0,  0,  // front bottom left  
        -1,  0,  0,  // rear bottom left
        -1,  0,  0,  // front top left

        -1,  0,  0,  // rear bottom left
        -1,  0,  0,  // rear top left
        -1,  0,  0,  // front top left

        // right face
         1,  0,  0,  // front bottom right
         1,  0,  0,  // rear bottom right
         1,  0,  0,  // front top right

         1,  0,  0,  // rear bottom right
         1,  0,  0,  // rear top right
         1,  0,  0,  // front top right
    };

    this -> texCoords = new GLfloat[12*3*2];
    for (int i = 0; i < 12*3*2; i += 12) {
        // bottom left
        this -> texCoords[i] = 0;
        this -> texCoords[i+1] = 0;

        // bottom right
        this -> texCoords[i+2] = 1;
        this -> texCoords[i+3] = 0;

        // top left
        this -> texCoords[i+4] = 0;
        this -> texCoords[i+5] = 1;

        // bottom right
        this -> texCoords[i+6] = 1;
        this -> texCoords[i+7] = 0;

        // top right
        this -> texCoords[i+8] = 1;
        this -> texCoords[i+9] = 1;

        // top left
        this -> texCoords[i+10] = 0;
        this -> texCoords[i+11] = 1;
    }

    this -> setColors(colors);
}