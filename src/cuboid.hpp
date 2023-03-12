#ifndef _blimp_CUBOID
#define _blimp_CUBOID

#include "geometry.hpp"

/** @file cuboid.hpp */

namespace blimp {

    //! A cuboid geometry.
    class Cuboid : public blimp::Geometry {
        public:
            /** The default constructor.
             * Creates a black `1x1x1` cube.
             * @param a The length of the cuboid's x axis
             * @param b The length of the cuboid's y axis
             * @param c The length of the cuboid's z axis
             * @param colors The colors of the cuboid's vertices
             */
            Cuboid(float a = 1.0f, float b = 1.0f, float c = 1.0f, ColorVector* colors = nullptr);
    };
    
}

#endif