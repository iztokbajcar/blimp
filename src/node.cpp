#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "node.hpp"

blimp::Node::Node() {
    this -> transformationMatrix = new glm::mat4(1.0f);
}

glm::mat4* blimp::Node::getTransformationMatrix() {
    return this -> transformationMatrix;
}

glm::vec3 blimp::Node::getTranslation() {
    return glm::vec3(
        (*this -> transformationMatrix)[3][0], 
        (*this -> transformationMatrix)[3][1], 
        (*this -> transformationMatrix)[3][2]
    ); 
}

glm::vec3 blimp::Node::getScale() {
    return glm::vec3(
        (*this -> transformationMatrix)[0][0],
        (*this -> transformationMatrix)[1][1],
        (*this -> transformationMatrix)[2][2]
    );
}

void blimp::Node::setTranslation(float x, float y, float z) {
    // translate the identity matrix by the specified vector
    *(this -> transformationMatrix) = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void blimp::Node::setScale(float x, float y, float z) {
    // scale the identity matrix by the specified vector
    *(this -> transformationMatrix) = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}

void blimp::Node::addChild(Node* child) {
    this -> children -> push_back(child);
}

void blimp::Node::removeChild(Node* child) {
    // remove every pointer to the child
    this -> children -> erase(
        std::remove(
            this -> children -> begin(), 
            this -> children -> end(),
            child
        ),
        this -> children -> end()
    );
}