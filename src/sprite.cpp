#include "sprite.hpp"
#include <iostream>

blimp::Rectangle blimp::Sprite::defaultGeometry = Rectangle(1.0f, 1.0f);
blimp::Material blimp::Sprite::defaultMaterial = Material();

blimp::Sprite::Sprite() : Mesh() {
    this -> geometry = &blimp::Sprite::defaultGeometry;
    this -> material = &blimp::Sprite::defaultMaterial;
}

blimp::Sprite::Sprite(Geometry* geometry, Material* material) : Mesh(geometry, material) {
}
