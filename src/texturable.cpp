#include "texturable.hpp"
#include <iostream>

blimp::TextureOptions blimp::Texturable::defaultTexOptions = TextureOptions(
    TextureOptions::WrapMode::REPEAT,
    TextureOptions::FilterMode::LINEAR
);

blimp::Texturable::Texturable() {
    this -> texture = nullptr;
    this -> texOptions = &blimp::Texturable::defaultTexOptions;
}

blimp::Texture* blimp::Texturable::getTexture() {
    return this -> texture;
}

void blimp::Texturable::setTexture(blimp::Texture* texture) {
    this -> texture = texture;
}

void blimp::Texturable::setTexture(blimp::Texture* texture, blimp::TextureOptions* options) {
    this -> texture = texture;
    this -> texOptions = options;
}

blimp::TextureOptions* blimp::Texturable::getTextureOptions() {
    return this -> texOptions;
}   

void blimp::Texturable::setTextureOptions(blimp::TextureOptions* options) {
    this -> texOptions = options;
}