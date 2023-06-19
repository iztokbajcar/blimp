#include "texture.hpp"
#include <iostream>

blimp::Texture::Texture(std::string filename) {
    // load the image
    this -> data = SOIL_load_image(filename.c_str(), &this -> width, &this -> height, 0, SOIL_LOAD_RGBA);
    
    if (this -> data == nullptr) {
        std::cout << "Error loading texture: " << filename << std::endl;
        exit(1);
    }

    this -> options = new TextureOptions();
}

blimp::Texture::Texture(std::string filename, TextureOptions* options) : Texture(filename){
    this -> options = options;
}

int blimp::Texture::getWidth() {
    return this -> width;
}

int blimp::Texture::getHeight() {
    return this -> height;
}

blimp::TextureOptions* blimp::Texture::getOptions() {
    return this -> options;
}   

unsigned char* blimp::Texture::getData() {
    return this -> data;
}