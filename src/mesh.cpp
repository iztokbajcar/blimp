#include "mesh.hpp"

blimp::Mesh::Mesh() {
    this -> geometry = nullptr;
    this -> material = nullptr;
    this -> texture = nullptr;
    this -> nodeType = blimp::Node::NODE_TYPE_MESH;
}

blimp::Mesh::Mesh(blimp::Geometry* geometry, blimp::Material* material) {
    this -> geometry = geometry;
    this -> material = material;
    this -> nodeType = blimp::Node::NODE_TYPE_MESH;
}

blimp::Geometry* blimp::Mesh::getGeometry() {
    return this -> geometry;
}

blimp::Material* blimp::Mesh::getMaterial() {
    return this -> material;
}

void blimp::Mesh::setGeometry(blimp::Geometry* geometry) {
    this -> geometry = geometry;
}

void blimp::Mesh::setMaterial(blimp::Material* material) {
    this -> material = material;
}

blimp::Texture* blimp::Mesh::getTexture() {
    return this -> texture;
}

void blimp::Mesh::setTexture(blimp::Texture* texture) {
    this -> texture = texture;
}