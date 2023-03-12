#ifndef _blimp_REGULAR_POLYGON
#define _blimp_REGULAR_POLYGON

#include "geometry.hpp"

/** @file regularpolygon.hpp */

namespace blimp {
    
    //! A regular polygon geometry.
    class RegularPolygon : public blimp::Geometry {
        public:
            /** The default constructor.
             * Creates a regular polygon with the given parameters.
             * The polygon has a depth of 0 and is centered at the origin, with the first vertex at (0, radius).
             * Vertices are ordered counter-clockwise, forming triangles that all contain the first vertex.
             * @param sides The number of sides of the polygon
             * @param radius The radius of the polygon
             * @param colors The colors of the polygon's vertices
            */
            RegularPolygon(int sides = 3, float radius = 0.5, ColorVector* colors = nullptr);
    };

}

#endif