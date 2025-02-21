#include "phongmaterial.hpp"

blimp::PhongMaterial::PhongMaterialVertexShader::PhongMaterialVertexShader(std::vector<ShaderFeature> shaderFeatures) : blimp::VertexShader(shaderFeatures) {

}

std::string blimp::PhongMaterial::PhongMaterialVertexShader::generateAbout() {
    return
        "// *************************************\n"
        "// *  Phong material - vertex shader   *\n"
        "// *************************************\n";
}

// blimp::PhongMaterial::PhongMaterialFragmentShader::PhongMaterialFragmentShader() : blimp::FragmentShader() {

// }

blimp::PhongMaterial::PhongMaterialFragmentShader::PhongMaterialFragmentShader(std::vector<ShaderFeature> shaderFeatures) : blimp::FragmentShader(shaderFeatures){
 
}

std::string blimp::PhongMaterial::PhongMaterialFragmentShader::generateAbout() {
    return
        "// ***************************************\n"
        "// *  Phong material - fragment shader   *\n"
        "// ***************************************\n";
}

std::string blimp::PhongMaterial::PhongMaterialFragmentShader::generateGlobals() {
    return
        FragmentShader::generateGlobals() +
        "vec4 calculateLightContribution(vec4 lightColor, float lightIntensity, vec4 diffuseColor, vec4 lightDir, vec4 normal, float specularFactor, float specular) {\n"
        "    vec4 c;"
        "    if (uUseTexture) {\n"
        "        c = texture(uTexture, vec2(vTexCoord.x / uTextureScaleS, vTexCoord.y / uTextureScaleT));\n"
        "    } else {\n"
        "        c = diffuseColor;\n"
        "    }\n"
        "    return (lightColor * lightIntensity) * (c * max(dot(lightDir, normal), 0.0) + specularFactor * lightColor * specular);\n"
        "}\n";
}

std::string blimp::PhongMaterial::PhongMaterialFragmentShader::generateMain() {
    return
        "void main() {\n"
        "    vec4 diffuseColor = vColor;\n"
        "    if (uUseTexture) {\n"
        "        diffuseColor = texture(uTexture, vec2(vTexCoord.x / uTextureScaleS, vTexCoord.y / uTextureScaleT));\n"
        "    }\n"
        "    vec4 normal = vec4(normalize(vNormal));\n"
        "    vec4 eyeDir = vec4(normalize(uCameraPos - vPos), 0.0);\n"
        "    float shininess = uMatShininess;\n"
        "    float specularFactor = uMatSpecular;\n"
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

blimp::PhongMaterial::PhongMaterialVertexShader blimp::PhongMaterial::defaultVertexShader = PhongMaterialVertexShader(
    std::vector<ShaderFeature> {
        ShaderFeature::USES_POSITION,
        ShaderFeature::USES_CAMERA_POSITION,
        ShaderFeature::USES_COLOR,
        ShaderFeature::USES_LIGHTS,
        ShaderFeature::USES_TEXTURES,
    }
);

blimp::PhongMaterial::PhongMaterialFragmentShader blimp::PhongMaterial::defaultFragmentShader = PhongMaterialFragmentShader(
    std::vector<ShaderFeature> {
        ShaderFeature::USES_POSITION,
        ShaderFeature::USES_CAMERA_POSITION,
        ShaderFeature::USES_COLOR,
        ShaderFeature::USES_LIGHTS,
        ShaderFeature::USES_TEXTURES,
    }
);

blimp::PhongMaterial::PhongMaterial() : Material() {
    this -> vertexShader = &blimp::PhongMaterial::defaultVertexShader;
    this -> fragmentShader = &blimp::PhongMaterial::defaultFragmentShader;

    this -> lights = true;
}

blimp::PhongMaterial::PhongMaterial(float shininess, float specular) : PhongMaterial() {
    this -> shininess = shininess;
    this -> specular = specular;
}