#include "color.hpp"

// definitions of Color constants
const float blimp::Color::BLACK[3] = {0.0f, 0.0f, 0.0f};
const float blimp::Color::SILVER[3] = {0.75f, 0.75f, 0.75f};
const float blimp::Color::GRAY[3] = {0.5f, 0.5f, 0.5f};
const float blimp::Color::WHITE[3] = {1.0f, 1.0f, 1.0f};
const float blimp::Color::MAROON[3] = {0.5f, 0.0f, 0.0f};
const float blimp::Color::RED[3] = {1.0f, 0.0f, 0.0f};
const float blimp::Color::PURPLE[3] = {0.5f, 0.0f, 0.5f};
const float blimp::Color::FUCHSIA[3] = {1.0f, 0.0f, 1.0f};
const float blimp::Color::GREEN[3] = {0.0f, 0.5f, 0.0f};
const float blimp::Color::LIME[3] = {0.0f, 1.0f, 0.0f};
const float blimp::Color::OLIVE[3] = {0.5f, 0.5f, 0.0f};
const float blimp::Color::YELLOW[3] = {1.0f, 1.0f, 0.0f};
const float blimp::Color::NAVY[3] = {0.0f, 0.0f, 0.5f};
const float blimp::Color::BLUE[3] = {0.0f, 0.0f, 1.0f};
const float blimp::Color::TEAL[3] = {0.0f, 0.5f, 0.5f};
const float blimp::Color::AQUA[3] = {0.0f, 1.0f, 1.0f};

blimp::Color::Color(float r, float g, float b) {
    this -> r = r;
    this -> g = g;
    this -> b = b;
}

blimp::Color::Color(float r, float g, float b, float a) {
    this -> r = r;
    this -> g = g;
    this -> b = b;
    this -> alpha = a;
}

blimp::Color::Color(const float rgb[3]) {
    this -> r = rgb[0];
    this -> g = rgb[1];
    this -> b = rgb[2];
    this -> alpha = 1.0f;
}

float blimp::Color::getR() {
    return this -> r;
}

float blimp::Color::getG() {
    return this -> g;
}

float blimp::Color::getB() {
    return this -> b;
}

float blimp::Color::getA() {
    return this -> alpha;
}

blimp::Color blimp::Color::fromRGB(float r, float g, float b) {
    return blimp::Color(r, g, b);
}