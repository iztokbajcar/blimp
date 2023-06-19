#include "textureoptions.hpp"

blimp::TextureOptions::TextureOptions() {
    this -> scaleS = 1.0f;
    this -> scaleT = 1.0f;
    this -> wrapS = WrapMode::REPEAT;
    this -> wrapT = WrapMode::REPEAT;
    this -> minFilterMode = FilterMode::LINEAR;
    this -> magFilterMode = FilterMode::LINEAR;
}

blimp::TextureOptions::TextureOptions(float scaleS, float scaleT) : TextureOptions() {
    this -> scaleS = scaleS;
    this -> scaleT = scaleT;
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

blimp::TextureOptions::TextureOptions(float scaleS, float scaleT, WrapMode wrapModeS, WrapMode wrapModeT, FilterMode minFilterMode, FilterMode magFilterMode) {
    this -> scaleS = scaleS;
    this -> scaleT = scaleT;
    this -> wrapS = wrapModeS;
    this -> wrapT = wrapModeT;
    this -> minFilterMode = minFilterMode;
    this -> magFilterMode = magFilterMode;
}

void blimp::TextureOptions::setScale(float scale) {
    this -> scaleS = scale;
    this -> scaleT = scale;
}

void blimp::TextureOptions::setScale(float scaleS, float scaleT) {
    this -> scaleS = scaleS;
    this -> scaleT = scaleT;
}

void blimp::TextureOptions::setScaleS(float scaleS) {
    this -> scaleS = scaleS;
}

void blimp::TextureOptions::setScaleT(float scaleT) {
    this -> scaleT = scaleT;
}

void blimp::TextureOptions::setWrapMode(WrapMode wrapMode) {
    this -> wrapS = wrapMode;
    this -> wrapT = wrapMode;
}

void blimp::TextureOptions::setWrapMode(WrapMode wrapModeS, WrapMode wrapModeT) {
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

void blimp::TextureOptions::setFilterMode(FilterMode minFilterMode, FilterMode magFilterMode) {
    this -> minFilterMode = minFilterMode;
    this -> magFilterMode = magFilterMode;
}

void blimp::TextureOptions::setMinFilterMode(FilterMode minFilterMode) {
    this -> minFilterMode = minFilterMode;
}

void blimp::TextureOptions::setMagFilterMode(FilterMode magFilterMode) {
    this -> magFilterMode = magFilterMode;
}

float blimp::TextureOptions::getScaleS() {
    return this -> scaleS;
}

float blimp::TextureOptions::getScaleT() {
    return this -> scaleT;
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