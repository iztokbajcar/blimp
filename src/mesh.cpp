#include "mesh.hpp"

blimp::Mesh::Mesh() {
    this -> geometry = nullptr;
    this -> material = nullptr;
}

blimp::Mesh::Mesh(blimp::Geometry* geometry, blimp::Material* material) {
    this -> geometry = geometry;
    this -> material = material;
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