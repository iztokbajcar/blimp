#include "orthographiccamera.hpp"

blimp::OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) {
    this -> left = left;
    this -> right = right;
    this -> bottom = bottom;
    this -> top = top;
    this -> near = near;
    this -> far = far;
    this -> nodeType = Node::NODE_TYPE_ORTHOGRAPHIC_CAMERA;
}

float blimp::OrthographicCamera::getLeft() {
    return this -> left;
}

float blimp::OrthographicCamera::getRight() {
    return this -> right;
}

float blimp::OrthographicCamera::getBottom() {
    return this -> bottom;
}

float blimp::OrthographicCamera::getTop() {
    return this -> top;
}

float blimp::OrthographicCamera::getNear() {
    return this -> near;
}

float blimp::OrthographicCamera::getFar() {
    return this -> far;
}

void blimp::OrthographicCamera::setLeft(float left) {
    this -> left = left;
}

void blimp::OrthographicCamera::setRight(float right) {
    this -> right = right;
}

void blimp::OrthographicCamera::setBottom(float bottom) {
    this -> bottom = bottom;
}

void blimp::OrthographicCamera::setTop(float top) {
    this -> top = top;
}

void blimp::OrthographicCamera::setNear(float near) {
    this -> near = near;
}

void blimp::OrthographicCamera::setFar(float far) {
    this -> far = far;
}

glm::mat4 blimp::OrthographicCamera::getViewMatrix() {
    glm::mat4 viewMatrix = glm::inverse(this -> getGlobalTransformationMatrix());
    return viewMatrix;
}

glm::mat4 blimp::OrthographicCamera::getProjectionMatrix() {
    return glm::ortho(
        this -> left,
        this -> right,
        this -> bottom,
        this -> top,
        this -> near,
        this -> far
    );
}
