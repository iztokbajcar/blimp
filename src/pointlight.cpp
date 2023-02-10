#include "pointlight.hpp"

blimp::PointLight::PointLight() {
    this -> nodeType = blimp::Node::NODE_TYPE_POINT_LIGHT;
}

blimp::PointLight::PointLight(blimp::Color color, float intensity, float attenuation) : blimp::Light(color, intensity) {
    this -> nodeType = blimp::Node::NODE_TYPE_POINT_LIGHT;
    this -> attenuation = attenuation;
}

float blimp::PointLight::getAttenuation() {
    return this -> attenuation;
}

void blimp::PointLight::setAttenuation(float attenuation) {
    this -> attenuation = attenuation;
}