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
    this -> rgb[0] = r;
    this -> rgb[1] = g;
    this -> rgb[2] = b;
}

blimp::Color::Color(float r, float g, float b, float a) {
    this -> rgb[0] = r;
    this -> rgb[1] = g;
    this -> rgb[2] = b;
    this -> alpha = a;
}

float blimp::Color::getR() {
    return this -> rgb[0];
}

float blimp::Color::getG() {
    return this -> rgb[1];
}

float blimp::Color::getB() {
    return this -> rgb[2];
}

float blimp::Color::getA() {
    return this -> alpha;
}

blimp::Color blimp::Color::fromRGB(float r, float g, float b) {
    return blimp::Color(r, g, b);
}