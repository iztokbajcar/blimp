#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "perspectivecamera.hpp"
#include <iostream>

blimp::PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far) {
    this -> fov = fov;
    this -> aspect = aspect;
    this -> near = near;
    this -> far = far;
}

float blimp::PerspectiveCamera::getFov() {
    return this -> fov;
}

float blimp::PerspectiveCamera::getNear() {
    return this -> near;
}

float blimp::PerspectiveCamera::getFar() {
    return this -> far;
}

glm::mat4 blimp::PerspectiveCamera::getViewMatrix() {
    // compute view matrix from camera position, target and up vector
    glm::mat4 viewMatrix = glm::inverse(this -> getGlobalTransformationMatrix());
    return viewMatrix;
}

glm::mat4 blimp::PerspectiveCamera::getProjectionMatrix() {
    return glm::perspective(
        this -> fov,
        this -> aspect,
        this -> near,
        this -> far
    );
}