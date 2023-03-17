#include "texture.hpp"
#include <iostream>

blimp::Texture::Texture(std::string filename) {
    // load the image
    this -> data = SOIL_load_image(filename.c_str(), &this -> width, &this -> height, 0, SOIL_LOAD_RGBA);
    
    if (this -> data == nullptr) {
        std::cout << "Error loading texture: " << filename << std::endl;
        exit(1);
    }
}

int blimp::Texture::getWidth() {
    return this -> width;
}

int blimp::Texture::getHeight() {
    return this -> height;
}

unsigned char* blimp::Texture::getData() {
    return this -> data;
}