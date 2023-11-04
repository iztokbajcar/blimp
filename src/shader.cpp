#include "shader.hpp"

blimp::Shader::Shader() {
    this -> source = "";
    this -> usesLights = false;
    this -> usesTextures = false;
    this -> type = ShaderType::VERTEX;

    this -> usesPosition = false;
    this -> usesColor = false;
    this -> usesNormals = false;
    this -> usesTextures = false;
}

blimp::Shader::Shader(std::vector<ShaderFeature> shaderFeatures) : Shader() {
    //! @todo Make better use of the shaderFeatures vector, especially for custom shaders.
    for (ShaderFeature feature : shaderFeatures) {
        if (feature == ShaderFeature::USES_POSITION) {
            this -> usesPosition = true;
        } else if (feature == ShaderFeature::USES_CAMERA_POSITION) {
            this -> usesCameraPosition = true;
        } else if (feature == ShaderFeature::USES_COLOR) {
            this -> usesColor = true;
        } else if (feature == ShaderFeature::USES_NORMALS) {
            this -> usesNormals = true;
        } else if (feature == ShaderFeature::USES_LIGHTS) {
            this -> usesNormals = true;
            this -> usesLights = true;
        } else if (feature == ShaderFeature::USES_TEXTURES) {
            this -> usesTextures = true;
        }
    }
}

std::string blimp::Shader::generateAbout() {
    return "";
}

std::string blimp::Shader::generateVersionTag() {
    return "#version 330 core\n";
}

std::string blimp::Shader::generateDefines() {
    return "";
}

std::string blimp::Shader::generateGlobals() {
    return "";
}

std::string blimp::Shader::generateUniforms() {
    return "";
}

std::string blimp::Shader::generateIns() {
    return "";
}

std::string blimp::Shader::generateOuts() {
    return "";
}

std::string blimp::Shader::generateMain() {
    return "void main() {}\n";
}

std::string* blimp::Shader::generateSource() {
    this -> source =
        this -> generateAbout() +
        this -> generateVersionTag() +
        this -> generateDefines() +
        this -> generateUniforms() +
        this -> generateIns() +
        this -> generateOuts() +
        this -> generateGlobals() +
        this -> generateMain();

    return &this -> source;
}