#include <glm/glm.hpp>
#include "camera.hpp"

blimp::Camera::Camera() {
    
}

float blimp::Camera::getFov() {
    return this -> fov;
}

void blimp::Camera::setFov(float fov) {
    this -> fov = fov;
}
