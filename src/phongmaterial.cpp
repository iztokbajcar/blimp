#include "phongmaterial.hpp"

std::string generateVertexShader() {
    return "#version 330 core\n"

        "uniform mat4 uModelMatrix;\n"
        "uniform mat4 uViewMatrix;\n"
        "uniform mat4 uProjectionMatrix;\n"

        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 1) in vec4 aColor;\n"
        "layout (location = 2) in vec3 aNormal;\n"
        "layout (location = 3) in vec2 aTexCoord;\n"

        "out vec3 vPos;\n"
        "out vec4 vColor;\n"
        "out vec4 vNormal;\n"
        "out vec2 vTexCoord;\n"

        "void main() {\n"
        "    vColor = aColor;\n"
        "    vNormal = normalize(uModelMatrix * vec4(aNormal, 0.0));\n"
        "    vPos = vec3(uModelMatrix * vec4(aPosition, 1.0));\n"
        "    vTexCoord = vec2(aTexCoord.x, 1.0f - aTexCoord.y);\n"  // flip the image, as SOIL loads it upside-down
        "    gl_Position = uProjectionMatrix * uViewMatrix * vec4(vPos, 1.0);\n"
        "}";
}

std::string generateFragmentShader(float shininess, float specular) {
    std::string shininessString = std::to_string(shininess);
    std::string specularString = std::to_string(specular);

    return "#version 330 core\n"
    "#define MAX_LIGHTS 100\n"
    "precision mediump float;\n"

    // light structs
    "struct ALight {\n"
    "    vec3 color;\n"
    "    float intensity;\n"
    "};\n"
    "struct DLight {\n"
    "    mat4 matrix;\n"  // global transformation matrix
    "    vec3 position;\n"
    "    vec3 color;\n"
    "    float intensity;\n"
    "};\n"
    "struct PLight {\n"
    "    mat4 matrix;\n"
    "    vec3 position;\n"
    "    vec3 color;\n"
    "    float intensity;\n"
    "    float attenuation;\n"
    "};\n"
    "struct SLight {\n"
    "    mat4 matrix;\n"
    "    vec3 position;\n"
    "    vec3 direction;\n"
    "    vec3 color;\n"
    "    float intensity;\n"
    "    float inner;\n"
    "    float outer;\n"
    "};\n"

    // uniforms
    "uniform vec3 uCameraPos;\n" 
    "uniform int uNumALights;\n"
    "uniform int uNumDLights;\n"
    "uniform int uNumPLights;\n"
    "uniform int uNumSLights;\n"
    "uniform ALight uALights[MAX_LIGHTS];\n"
    "uniform DLight uDLights[MAX_LIGHTS];\n"
    "uniform PLight uPLights[MAX_LIGHTS];\n"
    "uniform SLight uSLights[MAX_LIGHTS];\n"
    "uniform bool uUseTexture;\n"  // whether the shader should use a texture or not
    "uniform sampler2D uTexture;\n"

    "in vec3 vPos;\n"
    "in vec4 vColor;\n"
    "in vec4 vNormal;\n"
    "in vec2 vTexCoord;\n"
    "out vec4 oColor;\n"

    //! @todo add a way to determine how to mix texture with color and if we should use the texture at all
    "vec4 calculateLightContribution(vec4 lightColor, float lightIntensity, vec4 diffuseColor, vec4 lightDir, vec4 normal, float specularFactor, float specular) {\n"
    "    vec4 c;"
    "    if (uUseTexture) {\n"
    "        c = texture(uTexture, vTexCoord);\n"
    "    } else {\n"
    "        c = diffuseColor;\n"
    "    }\n"
    "    return (lightColor * lightIntensity) * c * dot(lightDir, normal) + specularFactor * lightColor * specular;\n"
    "}\n"

    "void main() {\n"
    "    vec4 diffuseColor = vColor;\n"
    "    vec4 normal = vec4(normalize(vNormal));\n"
    "    vec4 eyeDir = vec4(normalize(uCameraPos - vPos), 0.0);\n"
    "    float shininess = " + shininessString + ";\n"
    "    float specularFactor = " + specularString + ";\n"
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
    "        vec4 lightPos = vec4(uDLights[i].position, 1.0);\n"
    "        vec4 lightDir = vec4(normalize(lightPos - vec4(0.0f)));\n"  // light points to origin
    "        vec4 reflDir = normalize(reflect(-lightDir, normal));\n"
    "        vec4 lightColor = vec4(uDLights[i].color, 1.0);\n"
    "        float lightIntensity = uDLights[i].intensity;\n"
    "        float specular = max(0.0, pow(dot(reflDir, eyeDir), shininess));\n"
    "        vec4 newColor = calculateLightContribution(lightColor, lightIntensity, diffuseColor, lightDir, normal, specularFactor, specular);\n"
    "        color += clamp(newColor, 0.0, 1.0);\n"
    "    }\n"
        // point lights
    "    for (int i = 0; i < uNumPLights; i++) {\n"
    "        vec4 lightPos = vec4(uPLights[i].position, 1.0);\n"
    "        vec4 distanceVec = lightPos - vec4(vPos, 1.0);\n" 
    "        float dLength = length(distanceVec);\n"
    "        vec4 lightDir = normalize(distanceVec);\n"  // from fragment to light
    "        vec4 reflDir = normalize(reflect(-lightDir, normal));\n"
    "        vec4 lightColor = vec4(uPLights[i].color, 1.0) / (uPLights[i].attenuation * (dLength * dLength));\n"  // attenuates with square of distance
    "        float lightIntensity = uPLights[i].intensity;\n"
    "        float specular = max(0.0, pow(dot(reflDir, eyeDir), shininess));\n"
    "        vec4 newColor = calculateLightContribution(lightColor, lightIntensity, diffuseColor, lightDir, normal, specularFactor, specular);\n"
    "        color += clamp(newColor, 0.0, 1.0);\n"
    "    }\n"
        // spot lights
    "    for (int i = 0; i < uNumSLights; i++) {\n"
    "        vec4 lightPos = vec4(uSLights[i].position, 1.0);\n"
    "        vec4 distanceVec = lightPos - vec4(vPos, 0.0);\n"
    "        vec4 spotVec = -vec4(uSLights[i].direction, 0.0);\n" 
    "        vec4 lightDir = normalize(distanceVec);\n"  // from fragment to light
    "        vec4 reflDir = normalize(reflect(-lightDir, normal));\n"
    "        vec4 spotDir = normalize(spotVec);\n"
    "        float lightIntensity = uSLights[i].intensity;\n"
    "        float thetaCos = dot(lightDir, spotDir);\n"  // cosine of the angle between the vector pointing from light to fragment and the light direction
    "        if (thetaCos > uSLights[i].outer) {\n"  // if the angle is inside the outer cone
    "            vec4 lightColor;\n"
    "            if (thetaCos > uSLights[i].inner) {\n"
    "                lightColor = vec4(uSLights[i].color, 1.0);\n"
    "            } else {\n"
    "                float epsilon = (uSLights[i].inner - uSLights[i].outer);\n"
    "                float intensity = (thetaCos - uSLights[i].outer) / epsilon;\n"
    "                intensity = clamp(intensity, 0.0, 1.0);\n"
    "                lightColor = vec4(uSLights[i].color, 1.0) * intensity;\n" 
    "            }\n"
    "            float specular = max(0.0, pow(dot(reflDir, eyeDir), shininess));\n"
    "            vec4 newColor = calculateLightContribution(lightColor, lightIntensity, diffuseColor, lightDir, normal, specularFactor, specular);\n"
    "            color += clamp(newColor, 0.0, 1.0);\n"
    "        }\n"
    "    }\n"
    "    color.w = 1.0;\n"
    "    oColor = color;\n"
    "}";
}

blimp::PhongMaterial::PhongMaterial() {
    this -> shininess = 32.0f;
    this -> specular = 0.75f;
    this -> vertexShader = generateVertexShader();
    this -> fragmentShader = generateFragmentShader(this -> shininess, this -> specular);
    this -> lights = true;
    // this -> texture = nullptr;
}

blimp::PhongMaterial::PhongMaterial(float shininess, float specular) {
    this -> shininess = shininess;
    this -> specular = specular;
    this -> vertexShader = generateVertexShader();
    this -> fragmentShader = generateFragmentShader(this -> shininess, this -> specular);
    this -> lights = true;
    // this -> texture = nullptr;
}

float blimp::PhongMaterial::getShininess() {
    return this -> shininess;
}

void blimp::PhongMaterial::setShininess(float shininess) {
    this -> shininess = shininess;
}

float blimp::PhongMaterial::getSpecular() {
    return this -> specular;
}

void blimp::PhongMaterial::setSpecular(float specular) {
    this -> specular = specular;
}