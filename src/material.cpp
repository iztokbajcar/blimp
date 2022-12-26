#include <string>
#include <iostream>
#include "material.hpp"

blimp::Material::Material() {
    std::string defaultVertexShader = 
        "#version 330 core\n"
        "uniform mat4 uModelMatrix;\n"
        "uniform mat4 uViewMatrix;\n"
        "uniform mat4 uProjectionMatrix;\n"
        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 2) in vec3 aNormal;\n"
        "out vec4 vColor;\n"
        "void main() {\n"
        "   vec4 normal = normalize(uModelMatrix * vec4(aNormal, 0.0));\n"
        "   vColor = normal * 0.5f + 0.5f;\n"
        "   gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1.0);\n"
        "}\0";

    std::string defaultFragmentShader =
        "#version 330 core\n"
        "precision mediump float;\n"
        "in vec4 vColor;\n"
        "out vec4 oColor;\n"
        "void main() {\n"
        "   oColor = vColor;\n"
        "}\0";

    this -> vertexShader = defaultVertexShader;
    this -> fragmentShader = defaultFragmentShader;
}

blimp::Material::Material(std::string* vertexShader, std::string* fragmentShader) {
    this -> vertexShader = *vertexShader;
    this -> fragmentShader = *fragmentShader;
}

std::string* blimp::Material::getVertexShader() {
    return (&this -> vertexShader);
}

std::string* blimp::Material::getFragmentShader() {
    return (&this -> fragmentShader);
}