#ifndef _blimp_REGULAR_PYRAMID
#define _blimp_REGULAR_PYRAMID

#include "geometry.hpp"

/** @file regularpyramid.hpp **/

namespace blimp {

    class RegularPyramid : public Geometry {
        public:
            /** The default constructor.
             * Creates a regular pyramid with the given parameters.
             * @param sides The number of sides of the base polygon.
             * @param radius The radius of the base polygon.
             * @param height The height of the pyramid.
             * @param colors The colors of the pyramid's vertices.
            */
            RegularPyramid(int sides = 3, float radius = 0.5f, float height = 1.0f, ColorVector* colors = nullptr);
            // TODO apply colors, set texture coordinates
    };

}

#endif