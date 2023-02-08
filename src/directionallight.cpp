#include "directionallight.hpp"

blimp::DirectionalLight::DirectionalLight() : blimp::Light() {
    this -> nodeType = Node::NODE_TYPE_DIRECTIONAL_LIGHT;
}

blimp::DirectionalLight::DirectionalLight(blimp::Color color, float intensity) : blimp::Light(color, intensity) {
    this -> nodeType = Node::NODE_TYPE_DIRECTIONAL_LIGHT;
}