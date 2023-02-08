#include "ambientlight.hpp"

blimp::AmbientLight::AmbientLight() : blimp::Light() {
    this -> nodeType = Node::NODE_TYPE_AMBIENT_LIGHT;
}

blimp::AmbientLight::AmbientLight(blimp::Color color, float intensity) : blimp::Light(color, intensity) {
    this -> nodeType = Node::NODE_TYPE_AMBIENT_LIGHT;
}