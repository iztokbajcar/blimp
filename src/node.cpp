#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
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
    this -> transformationMatrix = glm::mat4(1.0f);
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
    // glm::mat4 rotationMatrix = glm::toMat4(this -> rotation);
    // glm::mat4 transformationMatrix = glm::mat4(1.0f);  // identity

    // transformationMatrix = glm::translate(transformationMatrix, this -> translation);
    // transformationMatrix *= rotationMatrix;
    // transformationMatrix = glm::scale(transformationMatrix, this -> scale);

    return transformationMatrix;
}

glm::mat4 blimp::Node::getParentTransformationMatrix() {
    if (this -> parent == nullptr) {
        return glm::mat4(1.0f);
    }
    return this -> parent -> getTransformationMatrix();
}

glm::mat4 blimp::Node::getGlobalTransformationMatrix() {
    if (this -> parent == nullptr) {
        return this -> getTransformationMatrix();
    } else {
        return this -> getParent() -> getGlobalTransformationMatrix() * this -> getTransformationMatrix();
    }
}

glm::vec3 blimp::Node::getTranslation() {
    return glm::vec3(this -> transformationMatrix[3]);
}

glm::quat blimp::Node::getRotation() {
    glm::vec3 translation;
    glm::quat rotation;
    glm::vec3 scale;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(this -> transformationMatrix, scale, rotation, translation, skew, perspective);
    return glm::conjugate(rotation);
}

glm::vec3 blimp::Node::getScale() {
    glm::vec3 translation;
    glm::quat rotation;
    glm::vec3 scale;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(this -> transformationMatrix, scale, rotation, translation, skew, perspective);
    return scale;
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

void blimp::Node::setTranslation(float x, float y, float z) {
    glm::vec3 scale, translation, skew;
    glm::vec4 perspective;
    glm::quat orientation;
    glm::decompose(this -> transformationMatrix, scale, orientation, translation, skew, perspective);

    this -> transformationMatrix = genTransformationMatrix(glm::vec3(), orientation, scale);
    this -> translate(x, y, z);
}

void blimp::Node::setRotation(float x, float y, float z) {
    glm::vec3 scale, translation, skew;
    glm::vec4 perspective;
    glm::quat orientation;
    glm::decompose(this -> transformationMatrix, scale, orientation, translation, skew, perspective);

    this -> transformationMatrix = genTransformationMatrix(translation, glm::quat(), scale);
    this -> rotate(x, y, z);
}

void blimp::Node::setScale(float x, float y, float z) {
    glm::vec3 scale, translation, skew;
    glm::vec4 perspective;
    glm::quat orientation;
    glm::decompose(this -> transformationMatrix, scale, orientation, translation, skew, perspective);

    this -> transformationMatrix = genTransformationMatrix(translation, orientation, glm::vec3(x, y, z));
}

void blimp::Node::translate(float x, float y, float z) {
    this -> transformationMatrix = glm::translate(this -> transformationMatrix, glm::vec3(x, y, z));
}

void blimp::Node::rotate(float x, float y, float z) {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), x, glm::vec3(1.0f, 0.0f, 0.0f));
    rotation = glm::rotate(rotation, y, glm::vec3(0.0f, 1.0f, 0.0f));
    rotation = glm::rotate(rotation, z, glm::vec3(0.0f, 0.0f, 1.0f));
    this -> transformationMatrix *= rotation;
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

glm::mat4 blimp::Node::genTransformationMatrix(glm::vec3 translation, glm::quat rotation, glm::vec3 scale) {
    glm::mat4 newMatrix = glm::mat4(1.0f);
    newMatrix = glm::translate(newMatrix, translation);
    newMatrix *= glm::toMat4(rotation);
    newMatrix = glm::scale(newMatrix, scale);

    return newMatrix;
}