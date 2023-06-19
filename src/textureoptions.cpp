#include "textureoptions.hpp"

blimp::TextureOptions::TextureOptions() {
    this -> wrapS = WrapMode::REPEAT;
    this -> wrapT = WrapMode::REPEAT;
    this -> minFilterMode = FilterMode::LINEAR;
    this -> magFilterMode = FilterMode::LINEAR;
}

blimp::TextureOptions::TextureOptions(WrapMode wrapMode) : TextureOptions() {
    this -> wrapS = wrapMode;
    this -> wrapT = wrapMode;
}

blimp::TextureOptions::TextureOptions(FilterMode filterMode) : TextureOptions() {
    this -> minFilterMode = filterMode;
    this -> magFilterMode = filterMode;
}

blimp::TextureOptions::TextureOptions(WrapMode wrapMode, FilterMode filterMode) : TextureOptions() {
    this -> wrapS = wrapMode;
    this -> wrapT = wrapMode;
    this -> minFilterMode = filterMode;
    this -> magFilterMode = filterMode;
}

blimp::TextureOptions::TextureOptions(WrapMode wrapModeS, WrapMode wrapModeT, FilterMode minFilterMode, FilterMode magFilterMode) {
    this -> wrapS = wrapModeS;
    this -> wrapT = wrapModeT;
    this -> minFilterMode = minFilterMode;
    this -> magFilterMode = magFilterMode;
}

void blimp::TextureOptions::setWrapMode(WrapMode wrapMode) {
    this -> wrapS = wrapMode;
    this -> wrapT = wrapMode;
}

void blimp::TextureOptions::setWrapModes(WrapMode wrapModeS, WrapMode wrapModeT) {
    this -> wrapS = wrapModeS;
    this -> wrapT = wrapModeT;
}

void blimp::TextureOptions::setWrapModeS(WrapMode wrapModeS) {
    this -> wrapS = wrapModeS;
}

void blimp::TextureOptions::setWrapModeT(WrapMode wrapModeT) {
    this -> wrapT = wrapModeT;
}

void blimp::TextureOptions::setFilterMode(FilterMode filterMode) {
    this -> minFilterMode = filterMode;
    this -> magFilterMode = filterMode;
}

void blimp::TextureOptions::setFilterModes(FilterMode minFilterMode, FilterMode magFilterMode) {
    this -> minFilterMode = minFilterMode;
    this -> magFilterMode = magFilterMode;
}

void blimp::TextureOptions::setMinFilterMode(FilterMode minFilterMode) {
    this -> minFilterMode = minFilterMode;
}

void blimp::TextureOptions::setMagFilterMode(FilterMode magFilterMode) {
    this -> magFilterMode = magFilterMode;
}

blimp::TextureOptions::WrapMode blimp::TextureOptions::getWrapModeS() {
    return this -> wrapS;
}

blimp::TextureOptions::WrapMode blimp::TextureOptions::getWrapModeT() {
    return this -> wrapT;
}

blimp::TextureOptions::FilterMode blimp::TextureOptions::getMinFilterMode() {
    return this -> minFilterMode;
}

blimp::TextureOptions::FilterMode blimp::TextureOptions::getMagFilterMode() {
    return this -> magFilterMode;
}