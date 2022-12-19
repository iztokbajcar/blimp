#include <glm/ext.hpp>
#include "perspectivecamera.hpp"
#include <iostream>

blimp::PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far) {
    this -> setViewMatrix(glm::perspective(fov, aspect, near, far));
}