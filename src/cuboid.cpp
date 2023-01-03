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

    this -> vertexCount = 12*3;
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

    // if colors are defined (not a null pointer), use the specified colors
    // otherwise default to red
    if (colors != nullptr) {
        this -> setColors(colors);
    } else {
        Color red = Color(Color::RED);
        ColorVector cv = ColorVector {red};
        this -> setColors(&cv);
    }
}