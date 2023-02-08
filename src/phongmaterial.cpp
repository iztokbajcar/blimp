#include "phongmaterial.hpp"

blimp::PhongMaterial::PhongMaterial() {
    std::string vertexShader = 
        "#version 330 core\n"
        "uniform mat4 uModelMatrix;\n"
        "uniform mat4 uViewMatrix;\n"
        "uniform mat4 uProjectionMatrix;\n"
        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 1) in vec4 aColor;\n"
        "layout (location = 2) in vec3 aNormal;\n"
        "out vec4 vColor;\n"
        "out vec3 vNormal;\n"
        "void main() {\n"
        "   vColor = aColor;\n"
        "   vNormal = aNormal;\n"
        "   gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1.0);\n"
        "}";

    std::string fragmentShader = 
        "#version 330 core\n"
        "#define MAX_LIGHTS 100\n"
        "precision mediump float;\n"
        "struct DLight {\n"
        "   vec3 pos;\n"
        "   vec3 color;\n"
        "   float intensity;\n"
        "};\n"
        "struct PLight {\n"
        "   vec3 pos;\n"
        "   vec3 color;\n"
        "   float intensity;\n"
        "};\n"
        "struct SLight {\n"
        "   vec3 pos;\n"
        "   vec3 color;\n"
        "   float intensity;\n"
        "};\n"
        "uniform int uNumDLights;\n"
        "uniform int uNumPLights;\n"
        "uniform int uNumSLights;\n"
        "uniform DLight uDLights[MAX_LIGHTS];\n"
        "uniform PLight uPLights[MAX_LIGHTS];\n"
        "uniform SLight uSLights[MAX_LIGHTS];\n"
        "in vec4 vColor;\n"
        "in vec3 vNormal;\n"
        "out vec4 oColor;\n"
        "void main() {\n"
        "   oColor = vColor;\n"
        "}";

    this -> vertexShader = vertexShader;
    this -> fragmentShader = fragmentShader;
    this -> lights = true;
}