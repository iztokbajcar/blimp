#include "texture2d.hpp"
#include <iostream>

blimp::Texture2D::Texture2D(std::string filename) {
    // load the image
    this -> data = SOIL_load_image(filename.c_str(), &this -> width, &this -> height, 0, SOIL_LOAD_RGBA);
    
    if (this -> data == nullptr) {
        std::cout << "Error loading texture: " << filename << std::endl;
        exit(1);
    }
}

int blimp::Texture2D::getWidth() {
    return this -> width;
}

int blimp::Texture2D::getHeight() {
    return this -> height;
}

unsigned char* blimp::Texture2D::getData() {
    return this -> data;
}