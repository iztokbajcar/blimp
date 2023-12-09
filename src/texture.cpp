#include "texture.hpp"

const int blimp::Texture::TEXTURE_TYPE_2D      = 0;
const int blimp::Texture::TEXTURE_TYPE_CUBEMAP = 1;

blimp::Texture::Texture() {
    this -> textureType = blimp::Texture::TEXTURE_TYPE_2D;
}

int blimp::Texture::getTextureType() {
    return this -> textureType;
}