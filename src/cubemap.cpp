#include "cubemap.hpp"

blimp::Cubemap::Cubemap(Texture2D* px, Texture2D* nx, Texture2D* py, Texture2D* ny, Texture2D* pz, Texture2D* nz) {
    this -> px = px;
    this -> nx = nx;
    this -> py = py;
    this -> ny = ny;
    this -> pz = pz;
    this -> nz = nz;
    this -> textureType = blimp::Texture::TEXTURE_TYPE_CUBEMAP;
}

blimp::Texture2D* blimp::Cubemap::getPX() {
    return this -> px;
}

blimp::Texture2D* blimp::Cubemap::getNX() {
    return this -> nx;
}

blimp::Texture2D* blimp::Cubemap::getPY() {
    return this -> py;
}

blimp::Texture2D* blimp::Cubemap::getNY() {
    return this -> ny;
}

blimp::Texture2D* blimp::Cubemap::getPZ() {
    return this -> pz;
}

blimp::Texture2D* blimp::Cubemap::getNZ() {
    return this -> nz;
}