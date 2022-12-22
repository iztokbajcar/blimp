#include <glm/glm.hpp>
#include "camera.hpp"

blimp::Camera::Camera() {
    
}

glm::mat4 blimp::Camera::getViewMatrix() {
    return glm::mat4(1.0f);
}

glm::mat4 blimp::Camera::getProjectionMatrix() {
    return glm::mat4(1.0f);
}

void blimp::Camera::setFov(float fov) {
    this -> fov = fov;
}
