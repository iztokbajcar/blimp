#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "node.hpp"

blimp::Node::Node(blimp::Geometry* geometry, blimp::Material* material) {
    this -> geometry = geometry;
    this -> material = material;
    this -> translation = glm::vec3(0.0f);
    this -> rotation = glm::vec3(0.0f);
    this -> scale = glm::vec3(1.0f);
}

glm::mat4 blimp::Node::getTransformationMatrix() {
    glm::mat4 rotationMatrix = glm::toMat4(this -> rotation);
    glm::mat4 transformationMatrix = glm::mat4(1.0f);  // identity

    transformationMatrix = glm::translate(transformationMatrix, this -> translation);
    transformationMatrix *= rotationMatrix;
    transformationMatrix = glm::scale(transformationMatrix, this -> scale);

    return transformationMatrix;
}

glm::vec3 blimp::Node::getTranslation() {
    return this -> translation; 
}

glm::quat blimp::Node::getRotation() {
    return this -> rotation;
}

glm::vec3 blimp::Node::getScale() {
    return this -> scale;
}

std::vector<blimp::Node*>* blimp::Node::getChildren() {
    return (&this -> children);
}

void blimp::Node::setTranslation(float x, float y, float z) {
    this -> translation = glm::vec3(x, y, z);
}

void blimp::Node::setRotation(float x, float y, float z) {
    this -> rotation = glm::quat(glm::vec3(x, y, z));
}

void blimp::Node::setScale(float x, float y, float z) {
    this -> scale = glm::vec3(x, y, z);
}

void blimp::Node::addChild(Node* child) {
    this -> children.push_back(child);
}

void blimp::Node::removeChild(Node* child) {
    // remove every pointer to the child
    this -> children.erase(
        std::remove(
            this -> children.begin(), 
            this -> children.end(),
            child
        ),
        this -> children.end()
    );
}