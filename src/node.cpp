#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "node.hpp"

blimp::Node::Node() {
    this -> geometry = nullptr;
    this -> material = nullptr;
    this -> translation = glm::vec3(0.0f);
    this -> rotation = glm::vec3(0.0f);
    this -> scale = glm::vec3(1.0f);
    this -> children = new std::vector<blimp::Node*>();
    this -> parentTransformationMatrix = glm::mat4(1.0f);
}

blimp::Node::Node(blimp::Geometry* geometry, blimp::Material* material) {
    this -> geometry = geometry;
    this -> material = material;
    this -> translation = glm::vec3(0.0f);
    this -> rotation = glm::vec3(0.0f);
    this -> scale = glm::vec3(1.0f);
    this -> children = new std::vector<blimp::Node*>();
    this -> parentTransformationMatrix = glm::mat4(1.0f);

}

blimp::Node::~Node() {
    delete this -> children;
}

glm::mat4 blimp::Node::getTransformationMatrix() {
    glm::mat4 rotationMatrix = glm::toMat4(this -> rotation);
    glm::mat4 transformationMatrix = glm::mat4(1.0f);  // identity

    transformationMatrix = glm::translate(transformationMatrix, this -> translation);
    transformationMatrix *= rotationMatrix;
    transformationMatrix = glm::scale(transformationMatrix, this -> scale);

    return transformationMatrix;
}

glm::mat4 blimp::Node::getParentTransformationMatrix() {
    return this -> parentTransformationMatrix;
}

glm::mat4 blimp::Node::getGlobalTransformationMatrix() {
    return this -> parentTransformationMatrix * this -> getTransformationMatrix();
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
    return this -> children;
}

blimp::Geometry* blimp::Node::getGeometry() {
    return this -> geometry;
}

blimp::Material* blimp::Node::getMaterial() {
    return this -> material;
}

void blimp::Node::setParentTransformationMatrix(glm::mat4 parentTransformationMatrix) {
    this -> parentTransformationMatrix = parentTransformationMatrix;
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
    child -> setParentTransformationMatrix(this -> getGlobalTransformationMatrix());
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

// traverse the node tree and return a vector containing all nodes
std::vector<blimp::Node*> blimp::Node::traverseChildren() {
    std::vector<Node*> nodes;

    // if this node has no children, return an empty vector
    if (this -> children -> empty())
        return nodes;

    // insert children
    for (Node* child: *(this -> children)) {
        // skip null pointers
        // if (child == nullptr)
        //     continue;

        nodes.push_back(child);
        std::vector<Node*> childNodes = child -> traverseChildren();
        nodes.insert(nodes.end(), childNodes.begin(), childNodes.end());
        
    }

    return nodes;
}