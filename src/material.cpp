#include <string>
#include "material.hpp"

blimp::Material::Material() {
    char* defaultVertexShader = 
        "#version 330 core"
        "layout (location = 0) in vec3 aPosition;"
        "layout (location = 1) in vec4 aColor;"
        "out vec4 vColor;"
        "void main() {"
        "   vColor = aColor;"
        "   gl_Position = vec4(position.x, position.y, position.z, 1.0);"
        "}\0";

    char* defaultFragmentShader =
        "#version 330 core"
        "precision mediump float;"
        "in vec4 vColor;"
        "out vec4 oColor;"
        "void main() {"
        "   oColor = vColor;"
        "}\0";

    this -> vertexShader = defaultVertexShader;
    this -> fragmentShader =defaultFragmentShader;
}

blimp::Material::Material(char* vertexShader, char* fragmentShader) {
    this -> vertexShader = vertexShader;
    this -> fragmentShader = fragmentShader;
}