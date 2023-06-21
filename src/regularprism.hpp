#ifndef _blimp_REGULAR_PRISM
#define _blimp_REGULAR_PRISM

#include "geometry.hpp"

/** @file regularprism.hpp */

namespace blimp {

    //! A prism with regular polygons as bases.
    class RegularPrism : public Geometry {
        public:
            /** The default constructor.
             * Creates a regular prism with the given parameters.
             * @param sides The number of sides of the base polygon.
             * @param radius The radius of the base polygon.
             * @param height The height of the prism.
             * @param colors The colors of the prism's vertices.
            */
            RegularPrism(int sides = 3, float radius = 0.5, float height = 1.0f, ColorVector* colors = nullptr);
            // TODO apply colors, set texture coordinates
    };

}

#endif