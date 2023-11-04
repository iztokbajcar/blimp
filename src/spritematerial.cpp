#include "spritematerial.hpp"

blimp::SpriteMaterial::SpriteMaterialVertexShader::SpriteMaterialVertexShader() : blimp::VertexShader() {

}

blimp::SpriteMaterial::SpriteMaterialVertexShader::SpriteMaterialVertexShader(std::vector<ShaderFeature> shaderFeatures) : blimp::VertexShader(shaderFeatures) {

}

std::string blimp::SpriteMaterial::SpriteMaterialVertexShader::generateAbout() {
    return
        "// *************************************\n"
        "// *  Sprite material - vertex shader  *\n"
        "// *************************************\n";
}

std::string blimp::SpriteMaterial::SpriteMaterialVertexShader::generateMain() {
    return
        "void main() {\n"
        "    // remove the rotation information from the model-view matrix\n"
        "    // (set to identity)\n"
        "    mat4 modelView = uViewMatrix * uModelMatrix;\n"
        "    modelView[0] = vec4(1.0, 0.0, 0.0, 0.0);\n"
        "    modelView[1] = vec4(0.0, 1.0, 0.0, 0.0);\n"
        "    modelView[2] = vec4(0.0, 0.0, 1.0, 0.0);\n"
        "    vPos = vec3(uModelMatrix * vec4(aPosition, 1.0));\n"
        "    vColor = aColor;\n"
        "    vNormal = normalize(uModelMatrix * vec4(aNormal, 0.0));\n"
        "    vTexCoord = vec2(aTexCoord.x, 1.0f - aTexCoord.y);\n"
        "    gl_Position = uProjectionMatrix * modelView * vec4(aPosition, 1.0);\n"
        "};\n";
}

blimp::SpriteMaterial::SpriteMaterialFragmentShader::SpriteMaterialFragmentShader() : blimp::FragmentShader() {

}

blimp::SpriteMaterial::SpriteMaterialFragmentShader::SpriteMaterialFragmentShader(std::vector<ShaderFeature> shaderFeatures) : blimp::FragmentShader(shaderFeatures) {

}

std::string blimp::SpriteMaterial::SpriteMaterialFragmentShader::generateAbout() {
    return
        "// ***************************************\n"
        "// *  Sprite material - fragment shader  *\n"
        "// ***************************************\n";
}

std::string blimp::SpriteMaterial::SpriteMaterialFragmentShader::generateMain() {
    return
        "void main() {\n"
        "    vec4 diffuseColor = vColor;\n"
        "    vec4 normal = vec4(normalize(vNormal));\n"
    

        "    vec4 color = diffuseColor;\n"
        "    if (uUseTexture) {\n"
        "         color = texture(uTexture, vec2(vTexCoord.x / uTextureScaleS, vTexCoord.y / uTextureScaleT));\n"
        "    }\n"

            // calculate color for every light
        // "    vec4 color = vec4(0.0, 0.0, 0.0, 1.0);\n"
        //     // ambient lights
        // "    for (int i = 0; i < uNumALights; i++) {\n"
        // "        vec4 lightColor = vec4(uALights[i].color, 1.0);\n"
        // "        float lightIntensity = uALights[i].intensity;\n"
        // "        vec4 newColor = (lightColor * lightIntensity) * c;\n"
        // "        color += newColor;\n"
        // "    }\n"
        //     // directional lights
        // "    for (int i = 0; i < uNumDLights; i++) {\n"
        // "        vec4 lightPos = vec4(uDLights[i].position, 1.0);\n"
        // "        vec4 lightDir = vec4(normalize(lightPos - vec4(0.0f)));\n"  // light points to origin
        // "        vec4 lightColor = vec4(uDLights[i].color, 1.0);\n"
        // "        float lightIntensity = uDLights[i].intensity;\n"
        // "        vec4 newColor = (lightColor * lightIntensity) * c * dot(lightDir, normal);\n"
        // "        color += clamp(newColor, 0.0, 1.0);\n"
        // "    }\n"
        //     // point lights
        // "    for (int i = 0; i < uNumPLights; i++) {\n"
        // "        vec4 lightPos = vec4(uPLights[i].position, 1.0);\n"
        // "        vec4 distanceVec = lightPos - vec4(vPos, 1.0);\n" 
        // "        float dLength = length(distanceVec);\n"
        // "        vec4 lightDir = normalize(distanceVec);\n"  // from fragment to light
        // "        vec4 lightColor = vec4(uPLights[i].color, 1.0) / (uPLights[i].attenuation * (dLength * dLength));\n"  // attenuates with square of distance
        // "        float lightIntensity = uPLights[i].intensity;\n"
        // "        vec4 newColor = (lightColor * lightIntensity) * c * dot(lightDir, normal);\n"
        // "        color += clamp(newColor, 0.0, 1.0);\n"
        // "    }\n"
        //     // spot lights
        // "    for (int i = 0; i < uNumSLights; i++) {\n"
        // "        vec4 lightPos = vec4(uSLights[i].position, 1.0);\n"
        // "        vec4 distanceVec = lightPos - vec4(vPos, 0.0);\n"
        // "        vec4 spotVec = -vec4(uSLights[i].direction, 0.0);\n" 
        // "        vec4 lightDir = normalize(distanceVec);\n"  // from fragment to light
        // "        vec4 spotDir = normalize(spotVec);\n"
        // "        float lightIntensity = uSLights[i].intensity;\n"
        // "        float thetaCos = dot(lightDir, spotDir);\n"  // cosine of the angle between the vector pointing from light to fragment and the light direction
        // "        if (thetaCos > uSLights[i].outer) {\n"  // if the angle is inside the outer cone
        // "            vec4 lightColor;\n"
        // "            if (thetaCos > uSLights[i].inner) {\n"
        // "                lightColor = vec4(uSLights[i].color, 1.0);\n"
        // "            } else {\n"
        // "                float epsilon = (uSLights[i].inner - uSLights[i].outer);\n"
        // "                float intensity = (thetaCos - uSLights[i].outer) / epsilon;\n"
        // "                intensity = clamp(intensity, 0.0, 1.0);\n"
        // "                lightColor = vec4(uSLights[i].color, 1.0) * intensity;\n" 
        // "            }\n"
        // "            vec4 newColor = (lightColor * lightIntensity) * c * dot(lightDir, normal);\n"
        // "            color += clamp(newColor, 0.0, 1.0);\n"
        // "        }\n"
        // "    }\n"
        "    color.w = 1.0;\n"
        "    oColor = color;\n"
        "}";
}

blimp::SpriteMaterial::SpriteMaterialVertexShader blimp::SpriteMaterial::defaultVertexShader = SpriteMaterialVertexShader(
    std::vector<ShaderFeature> {
        ShaderFeature::USES_POSITION,
        ShaderFeature::USES_COLOR,
        ShaderFeature::USES_LIGHTS,
        ShaderFeature::USES_TEXTURES,
        ShaderFeature::USES_CAMERA_POSITION
    }
);

blimp::SpriteMaterial::SpriteMaterialFragmentShader blimp::SpriteMaterial::defaultFragmentShader = SpriteMaterialFragmentShader(
    std::vector<ShaderFeature> {
        ShaderFeature::USES_POSITION,
        ShaderFeature::USES_COLOR,
        ShaderFeature::USES_LIGHTS,
        ShaderFeature::USES_TEXTURES,
        ShaderFeature::USES_CAMERA_POSITION
    }
);

blimp::SpriteMaterial::SpriteMaterial() : Material() {
    this -> vertexShader = &blimp::SpriteMaterial::defaultVertexShader;
    this -> fragmentShader = &blimp::SpriteMaterial::defaultFragmentShader;

    this -> lights = true;
}
