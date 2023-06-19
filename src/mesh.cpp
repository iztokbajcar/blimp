#include "mesh.hpp"

blimp::Mesh::Mesh() {
    this -> geometry = nullptr;
    this -> material = nullptr;
    this -> texture = nullptr;
    this -> texOptions = new blimp::TextureOptions();
    this -> usingDefaultTexOptions = true;
    this -> nodeType = blimp::Node::NODE_TYPE_MESH;
}

blimp::Mesh::Mesh(blimp::Geometry* geometry, blimp::Material* material) : Mesh() {
    this -> geometry = geometry;
    this -> material = material;
}

blimp::Mesh::~Mesh() {
    if (this -> usingDefaultTexOptions) {
        delete this -> texOptions;
    }
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

void blimp::Mesh::setTexture(blimp::Texture* texture, blimp::TextureOptions* options) {
    this -> texture = texture;
    this -> texOptions = options;
    this -> usingDefaultTexOptions = false;
}

blimp::TextureOptions* blimp::Mesh::getTextureOptions() {
    return this -> texOptions;
}   

void blimp::Mesh::setTextureOptions(blimp::TextureOptions* options) {
    // if the default texture options are being used, delete the object,
    // because it was created in the constructor
    if (this -> usingDefaultTexOptions) {
        delete this -> texOptions;
    }

    this -> texOptions = options;
}