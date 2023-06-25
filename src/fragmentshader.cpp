#include "fragmentshader.hpp"

blimp::FragmentShader::FragmentShader() : Shader() {
    this -> type = ShaderType::FRAGMENT;
}

blimp::FragmentShader::FragmentShader(std::vector<ShaderFeature> shaderFeatures) : Shader(shaderFeatures) {
    this -> type = ShaderType::FRAGMENT;
}

std::string blimp::FragmentShader::generateDefines() {
    std::string definesChunk = "";

    if (this -> usesLights) {
        definesChunk += "#define MAX_LIGHTS 100\n";
    }
    
    definesChunk += "precision mediump float;\n";

    if (this -> usesLights) {
        // light structs
        definesChunk += 
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
            "};\n";
    }

    return definesChunk;
}

std::string blimp::FragmentShader::generateGlobals() {
    return "";
}

std::string blimp::FragmentShader::generateUniforms() {
    std::string uniformsChunk = "";

    if (this -> usesPosition) {
        uniformsChunk += 
            "uniform mat4 uViewMatrix;\n"
            "uniform mat4 uProjectionMatrix;\n";
    }
    if (this -> usesCameraPosition) {
        uniformsChunk +=
            "uniform vec3 uCameraPos;\n";
    }
    if (this -> usesLights) {
        uniformsChunk += 
            "uniform int uNumALights;\n"
            "uniform int uNumDLights;\n"
            "uniform int uNumPLights;\n"
            "uniform int uNumSLights;\n"
            "uniform ALight uALights[MAX_LIGHTS];\n"
            "uniform DLight uDLights[MAX_LIGHTS];\n"
            "uniform PLight uPLights[MAX_LIGHTS];\n"
            "uniform SLight uSLights[MAX_LIGHTS];\n";
    }
    if (this -> usesTextures) {
        uniformsChunk += 
            "uniform bool uUseTexture;\n"
            "uniform sampler2D uTexture;\n"
            "uniform float uTextureScaleS;\n"
            "uniform float uTextureScaleT;\n";
    }

    return uniformsChunk;
}

std::string blimp::FragmentShader::generateIns() {
    return
        "in vec3 vPos;\n"
        "in vec4 vColor;\n"
        "in vec4 vNormal;\n"
        "in vec2 vTexCoord;\n";
}

std::string blimp::FragmentShader::generateOuts() {
    return
        "out vec4 oColor;\n";

}

std::string blimp::FragmentShader::generateMain() {
    std::string mainChunk = "void main() {\n";

    //! @todo generate based on features
    if (this -> usesLights) {
        mainChunk +=
            "    vec4 diffuseColor = vColor;\n"
            "    vec4 normal = vec4(normalize(vNormal));\n"

            "    vec4 c = diffuseColor;\n"
            "    if (uUseTexture) {\n"
            "         c = texture(uTexture, vec2(vTexCoord.x / uTextureScaleS, vTexCoord.y / uTextureScaleT));\n"
            "    }\n"

                // calculate color for every light
            "    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);\n"
                // ambient lights
            "    for (int i = 0; i < uNumALights; i++) {\n"
            "        vec4 lightColor = vec4(uALights[i].color, 1.0);\n"
            "        float lightIntensity = uALights[i].intensity;\n"
            "        vec4 newColor = (lightColor * lightIntensity) * c;\n"
            "        color += newColor;\n"
            "    }\n"
                // directional lights
            "    for (int i = 0; i < uNumDLights; i++) {\n"
            "        vec4 lightPos = vec4(uDLights[i].position, 1.0);\n"
            "        vec4 lightDir = vec4(normalize(lightPos - vec4(0.0f)));\n"  // light points to origin
            "        vec4 lightColor = vec4(uDLights[i].color, 1.0);\n"
            "        float lightIntensity = uDLights[i].intensity;\n"
            "        vec4 newColor = (lightColor * lightIntensity) * c * dot(lightDir, normal);\n"
            "        color += clamp(newColor, 0.0, 1.0);\n"
            "    }\n"
                // point lights
            "    for (int i = 0; i < uNumPLights; i++) {\n"
            "        vec4 lightPos = vec4(uPLights[i].position, 1.0);\n"
            "        vec4 distanceVec = lightPos - vec4(vPos, 1.0);\n" 
            "        float dLength = length(distanceVec);\n"
            "        vec4 lightDir = normalize(distanceVec);\n"  // from fragment to light
            "        vec4 lightColor = vec4(uPLights[i].color, 1.0) / (uPLights[i].attenuation * (dLength * dLength));\n"  // attenuates with square of distance
            "        float lightIntensity = uPLights[i].intensity;\n"
            "        vec4 newColor = (lightColor * lightIntensity) * c * dot(lightDir, normal);\n"
            "        color += clamp(newColor, 0.0, 1.0);\n"
            "    }\n"
                // spot lights
            "    for (int i = 0; i < uNumSLights; i++) {\n"
            "        vec4 lightPos = vec4(uSLights[i].position, 1.0);\n"
            "        vec4 distanceVec = lightPos - vec4(vPos, 0.0);\n"
            "        vec4 spotVec = -vec4(uSLights[i].direction, 0.0);\n" 
            "        vec4 lightDir = normalize(distanceVec);\n"  // from fragment to light
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
            "            vec4 newColor = (lightColor * lightIntensity) * c * dot(lightDir, normal);\n"
            "            color += clamp(newColor, 0.0, 1.0);\n"
            "        }\n"
            "    }\n"
            "    color.w = 1.0;\n"
            "    oColor = color;\n";
    } else {
        mainChunk += "oColor = vColor;\n";
    }
    
    mainChunk += "}\n";

    return mainChunk;
}