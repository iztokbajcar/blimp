#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "node.hpp"

const int blimp::Node::NODE_TYPE_GROUP                  = 0;
const int blimp::Node::NODE_TYPE_MESH                   = 1;
const int blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT      = 2;
const int blimp::Node::NODE_TYPE_POINT_LIGHT            = 3;
const int blimp::Node::NODE_TYPE_SPOT_LIGHT             = 4;
const int blimp::Node::NODE_TYPE_AMBIENT_LIGHT          = 5;
const int blimp::Node::NODE_TYPE_PERSPECTIVE_CAMERA     = 6;
const int blimp::Node::NODE_TYPE_ORTHOGRAPHIC_CAMERA    = 7;

blimp::Node::Node() {
    this -> translation = glm::vec3(0.0f);
    this -> rotation = glm::vec3(0.0f);
    this -> scale = glm::vec3(1.0f);
    this -> parent = nullptr;
    this -> children = new std::vector<blimp::Node*>();
    this -> parentTransformationMatrix = glm::mat4(1.0f);
    this -> nodeType = blimp::Node::NODE_TYPE_GROUP;
}

blimp::Node::~Node() {
    delete this -> children;
}

int blimp::Node::getNodeType() {
    return this -> nodeType;
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
    if (this -> parent == nullptr) {
        return glm::mat4(1.0f);
    }
    return this -> parent -> getTransformationMatrix();
}

//! TODO fix
glm::mat4 blimp::Node::getGlobalTransformationMatrix() {
    if (this -> parent == nullptr) {
        return this -> getTransformationMatrix();
    } else {
        return this -> getParent() -> getGlobalTransformationMatrix() * this -> getTransformationMatrix();
    }
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

glm::vec3 blimp::Node::getForwardDirection() {
    glm::mat4 transformationMatrix = this -> getGlobalTransformationMatrix();
    glm::vec4 forward = transformationMatrix * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);  // by default, the node will look in the positive z direction
    return glm::normalize(glm::vec3(forward));
}

std::vector<blimp::Node*>* blimp::Node::getChildren() {
    return this -> children;
}

// void blimp::Node::setParentTransformationMatrix(glm::mat4 parentTransformationMatrix) {
//     this -> parentTransformationMatrix = parentTransformationMatrix;
// }

//! TODO operate on a transformation matrix
void blimp::Node::setTranslation(float x, float y, float z) {
    this -> translation = glm::vec3(x, y, z);
}

void blimp::Node::setRotation(float x, float y, float z) {
    this -> rotation = glm::quat(glm::vec3(x, y, z));
}

void blimp::Node::translate(float x, float y, float z) {
    this -> translation += glm::vec3(x, y, z);
}

void blimp::Node::rotate(float x, float y, float z) {
    this -> rotation = glm::quat(glm::vec3(x, y, z)) * this -> rotation;
}

void blimp::Node::setScale(float x, float y, float z) {
    this -> scale = glm::vec3(x, y, z);
}

void blimp::Node::addChild(Node* child) {
    child -> setParent(this);
    this -> children -> push_back(child);
}

void blimp::Node::removeChild(Node* child) {
    child -> setParent(nullptr);

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

blimp::Node* blimp::Node::getParent() {
    return this -> parent;
}

void blimp::Node::setParent(Node* parent) {
    this -> parent = parent;
}