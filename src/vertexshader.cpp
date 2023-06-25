#include "vertexshader.hpp"

blimp::VertexShader::VertexShader() : Shader() {
    this -> type = ShaderType::VERTEX;
}

blimp::VertexShader::VertexShader(std::vector<ShaderFeature> shaderFeatures) : Shader(shaderFeatures) {
    this -> type = ShaderType::VERTEX;
}

std::string blimp::VertexShader::generateDefines() {
    return "";
}

std::string blimp::VertexShader::generateGlobals() {
    return "";
}

std::string blimp::VertexShader::generateUniforms() {
    std::string uniformsChunk = "";

    if (this -> usesPosition) {
        uniformsChunk += 
            "uniform mat4 uModelMatrix;\n"
            "uniform mat4 uViewMatrix;\n"
            "uniform mat4 uProjectionMatrix;\n";
    }

    return uniformsChunk;
}

std::string blimp::VertexShader::generateIns() {
    std::string insChunk = "";

    if (this -> usesPosition) {
        insChunk += "layout (location = 0) in vec3 aPosition;\n";
    }
    if (this -> usesColor) {
        insChunk += "layout (location = 1) in vec4 aColor;\n";
    }
    if (this -> usesNormals) {
        insChunk += "layout (location = 2) in vec3 aNormal;\n";
    }
    if (this -> usesTextures) {
        insChunk += "layout (location = 3) in vec2 aTexCoord;\n";
    }

    return insChunk;
}

std::string blimp::VertexShader::generateOuts() {
    std::string outsChunk = "";

    if (this -> usesPosition) {
        outsChunk += "out vec3 vPos;\n";
    }
    if (this -> usesColor) {
        outsChunk += "out vec4 vColor;\n";
    }
    if (this -> usesNormals) {
        outsChunk += "out vec4 vNormal;\n";
    }
    if (this -> usesTextures) {
        outsChunk += "out vec2 vTexCoord;\n";
    }

    return outsChunk;
}

std::string blimp::VertexShader::generateMain() {
    std::string mainChunk = "void main() {\n";

    if (this -> usesPosition) {
        mainChunk += "    vPos = vec3(uModelMatrix * vec4(aPosition, 1.0));\n";
    }
    if (this -> usesColor) { 
        mainChunk += "    vColor = aColor;\n";
    }
    if (this -> usesNormals) {
        mainChunk += "    vNormal = normalize(uModelMatrix * vec4(aNormal, 0.0));\n";
    }
    if (this -> usesTextures) {
        mainChunk += "    vTexCoord = vec2(aTexCoord.x, 1.0f - aTexCoord.y);\n";  // flip the image, as SOIL loads it upside-down
    }

    if (this -> usesPosition) {
        mainChunk += "    gl_Position = uProjectionMatrix * uViewMatrix * vec4(vPos, 1.0);\n";  // TODO this requires USES_POSITION to be true
    } else {
        mainChunk += "    gl_Position = vec4(vPos, 1.0);\n";
    }

    mainChunk += "}\n";

    return mainChunk;
}