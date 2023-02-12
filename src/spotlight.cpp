#include "spotlight.hpp"

blimp::SpotLight::SpotLight() {
    this -> nodeType = blimp::Node::NODE_TYPE_SPOT_LIGHT;
    this -> inner = 0.9f;
    this -> outer = 0.85f;
}

blimp::SpotLight::SpotLight(blimp::Color color, float intensity, float inner, float outer) : blimp::Light(color, intensity) {
    this -> nodeType = blimp::Node::NODE_TYPE_SPOT_LIGHT;
    this -> inner = inner;
    this -> outer = outer;
}

float blimp::SpotLight::getInnerCutoff() {
    return this -> inner;
}

float blimp::SpotLight::getOuterCutoff() {
    return this -> outer;
}

void blimp::SpotLight::setInnerCutoff(float inner) {
    this -> inner = inner;
}

void blimp::SpotLight::setOuterCutoff(float outer) {
    this -> outer = outer;
}