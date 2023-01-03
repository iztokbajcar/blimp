#ifndef _blimp_CUBOID
#define _blimp_CUBOID

#include "geometry.hpp"

namespace blimp {

    class Cuboid : public blimp::Geometry {
        public:
            Cuboid(float a = 1.0f, float b = 1.0f, float c = 1.0f, ColorVector* colors = nullptr);
    };
    
}

#endif