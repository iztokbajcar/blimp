#include <glm/glm.hpp>
#include "camera.hpp"

blimp::Camera::Camera() {

}

glm::mat4 blimp::Camera::getViewMatrix() {
    return this -> viewMatrix;
}

void blimp::Camera::setViewMatrix(glm::mat4 viewMatrix) {
    this -> viewMatrix = viewMatrix;
}