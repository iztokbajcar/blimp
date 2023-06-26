#include <string>
#include <iostream>

#include "material.hpp"
#include "shader.hpp"
#include "vertexshader.hpp"
#include "fragmentshader.hpp"

blimp::VertexShader blimp::Material::defaultVertexShader = VertexShader(
    std::vector<ShaderFeature> {
        ShaderFeature::USES_POSITION,
        ShaderFeature::USES_COLOR,
        ShaderFeature::USES_TEXTURES,
    }
);

blimp::FragmentShader blimp::Material::defaultFragmentShader = FragmentShader(
    std::vector<ShaderFeature> {
        ShaderFeature::USES_POSITION,
        ShaderFeature::USES_COLOR,
        ShaderFeature::USES_TEXTURES,
    }
);

blimp::Material::Material() {
    this -> vertexShader = &blimp::Material::defaultVertexShader;
    this -> fragmentShader = &blimp::Material::defaultFragmentShader;
    
    this -> shininess = 32.0f;
    this -> specular = 0.75f;
}

blimp::Material::Material(VertexShader* vertexShader, FragmentShader* fragmentShader) {
    this -> vertexShader = vertexShader;
    this -> fragmentShader = fragmentShader;

    this -> shininess = 32.0f;
    this -> specular = 0.75f;
}


blimp::VertexShader* blimp::Material::getVertexShader() {
    return this -> vertexShader;
}

blimp::FragmentShader* blimp::Material::getFragmentShader() {
    return this -> fragmentShader;
}

bool blimp::Material::usesLights() {
    return (this -> lights);
}

void blimp::Material::setUsesLights(bool usesLights) {
    this -> lights = usesLights;
}


float blimp::Material::getShininess() {
    return this -> shininess;
}

void blimp::Material::setShininess(float shininess) {
    this -> shininess = shininess;
}

float blimp::Material::getSpecular() {
    return this -> specular;
}

void blimp::Material::setSpecular(float specular) {
    this -> specular = specular;
}
