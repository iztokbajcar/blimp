#include "mesh.hpp"

blimp::Mesh::Mesh() {
    this -> geometry = nullptr;
    this -> material = nullptr;
}

blimp::Mesh::Mesh(blimp::Geometry* geometry, blimp::Material* material) {
    this -> geometry = geometry;
    this -> material = material;
}

blimp::Mesh::~Mesh() {
    delete this -> geometry;
    delete this -> material;
}

blimp::Geometry* blimp::Mesh::getGeometry() {
    return this -> geometry;
}

blimp::Material* blimp::Mesh::getMaterial() {
    return this -> material;
}