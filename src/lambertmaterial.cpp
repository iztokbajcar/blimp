#include "lambertmaterial.hpp"

blimp::LambertMaterial::LambertMaterial() {
    std::string vertexShader = 
        "#version 330 core\n"

        "uniform mat4 uModelMatrix;\n"
        "uniform mat4 uViewMatrix;\n"
        "uniform mat4 uProjectionMatrix;\n"

        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 1) in vec4 aColor;\n"
        "layout (location = 2) in vec3 aNormal;\n"

        "out vec3 vPos;\n"
        "out vec4 vColor;\n"
        "out vec3 vNormal;\n"

        "void main() {\n"
        "    vColor = aColor;\n"
        "    vNormal = aNormal;\n"
        "    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1.0);\n"
        "    vPos = vec3(gl_Position);\n"
        "}";

    std::string fragmentShader = 
        "#version 330 core\n"
        "#define MAX_LIGHTS 100\n"
        "precision mediump float;\n"

        // light structs
        "struct ALight {\n"
        "    vec3 color;\n"
        "    float intensity;\n"
        "};\n"
        "struct DLight {\n"
        "    vec3 position;\n"
        "    vec3 color;\n"
        "    float intensity;\n"
        "};\n"
        // TODO
        "//struct PLight {\n"
        "//    vec3 position;\n"
        "//    vec3 color;\n"
        "//    float intensity;\n"
        "//};\n"
        // TODO
        "//struct SLight {\n"
        "//    vec3 position;\n"
        "//    vec3 color;\n"
        "//    float intensity;\n"
        "//};\n"

        // uniforms
        "uniform int uNumALights;\n"
        "uniform int uNumDLights;\n"
        "//uniform int uNumPLights;\n"
        "//uniform int uNumSLights;\n"
        "uniform ALight uALights[MAX_LIGHTS];\n"
        "uniform DLight uDLights[MAX_LIGHTS];\n"
        "//uniform PLight uPLights[MAX_LIGHTS];\n"
        "//uniform SLight uSLights[MAX_LIGHTS];\n"

        "in vec3 vPos;\n"
        "in vec4 vColor;\n"
        "in vec3 vNormal;\n"
        "out vec4 oColor;\n"

        "void main() {\n"
        "    vec4 diffuseColor = vColor;\n"
        "    vec4 normal = vec4(normalize(vNormal), 0.0);\n"

             // calculate color for every light
        "    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);\n"
             // ambient lights
        "    for (int i = 0; i < uNumALights; i++) {\n"
        "        vec4 lightColor = vec4(uALights[i].color, 1.0);\n"
        "        float lightIntensity = uALights[i].intensity;\n"
        "        vec4 newColor = (lightColor * lightIntensity) * diffuseColor;\n"
        "        color += newColor;\n"
        "    }\n"
             // directional lights
        "    for (int i = 0; i < uNumDLights; i++) {\n"
        "        vec4 lightColor = vec4(uDLights[i].color, 1.0);\n"
        "        vec4 lightDir = vec4(normalize(uDLights[i].position - vPos), 1.0);\n"  // from fragment to light
        "        float lightIntensity = uDLights[i].intensity;\n"
        "        vec4 newColor = (lightColor * lightIntensity) * diffuseColor * dot(lightDir, normal);\n"
        "        color += newColor;\n"
        "    }\n"
             // TODO other light types
        "    oColor = color;\n"
        // "    oColor = vec4(1.0, 1.0, 0.0, 1.0);\n"
        "}";

    this -> vertexShader = vertexShader;
    this -> fragmentShader = fragmentShader;
    this -> lights = true;
}