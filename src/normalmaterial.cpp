#include "normalmaterial.hpp"
#include <iostream>

blimp::NormalMaterial::NormalMaterialVertexShader::NormalMaterialVertexShader(std::vector<ShaderFeature> shaderFeatures) : blimp::VertexShader(shaderFeatures) {

}

std::string blimp::NormalMaterial::NormalMaterialVertexShader::generateAbout() {
    return 
        "// *************************************\n"
        "// *  Normal material - vertex shader  *\n"
        "// *************************************\n";
}

std::string blimp::NormalMaterial::NormalMaterialVertexShader::generateMain() {
    return 
        "void main() {\n"
        "   vec4 normal = normalize(uModelMatrix * vec4(aNormal, 0.0));\n"
        "   vColor = normal * 0.5f + 0.5f;\n"
        "   gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1.0);\n"
        "}";
}

blimp::NormalMaterial::NormalMaterialFragmentShader::NormalMaterialFragmentShader(std::vector<ShaderFeature> shaderFeatures) : blimp::FragmentShader(shaderFeatures) {
    
}

std::string blimp::NormalMaterial::NormalMaterialFragmentShader::generateAbout() {
    return 
        "// ***************************************\n"
        "// *  Normal material - fragment shader  *\n"
        "// ***************************************\n";
}

blimp::NormalMaterial::NormalMaterialVertexShader blimp::NormalMaterial::defaultVertexShader = NormalMaterialVertexShader(
    std::vector<ShaderFeature> {
        ShaderFeature::USES_POSITION,
        ShaderFeature::USES_COLOR,
        ShaderFeature::USES_NORMALS
    }
);

blimp::NormalMaterial::NormalMaterialFragmentShader blimp::NormalMaterial::defaultFragmentShader = NormalMaterialFragmentShader(
    std::vector<ShaderFeature> {
        ShaderFeature::USES_POSITION,
        ShaderFeature::USES_COLOR,
        ShaderFeature::USES_NORMALS
    }
);

blimp::NormalMaterial::NormalMaterial() {
    this -> vertexShader = &blimp::NormalMaterial::defaultVertexShader;
    this -> fragmentShader = &blimp::NormalMaterial::defaultFragmentShader;
}