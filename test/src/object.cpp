#include "object.hpp"

blimp::Object::Object(blimp::Geometry* geometry, blimp::Material* material) {
    this -> geometry = geometry;
    this -> material = material;
}