#include "light.hpp"

blimp::Light::Light() {
    this -> nodeType = blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT;
    this -> color = blimp::Color(blimp::Color::WHITE);
    this -> intensity = 1.0f;
}

blimp::Light::Light(Color color, float intensity) {
    this -> nodeType = blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT;
    this -> color = color;
    this -> intensity = intensity;
}

blimp::Color* blimp::Light::getColor() {
    return &this -> color;
}

float blimp::Light::getIntensity() {
    return this -> intensity;
}

void blimp::Light::setColor(blimp::Color color) {
    this -> color = color;
}

void blimp::Light::setIntensity(float intensity) {
    this -> intensity = intensity;
}