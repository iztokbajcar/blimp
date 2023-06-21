#ifndef _blimp_REGULAR_POLYGON
#define _blimp_REGULAR_POLYGON

#include "geometry.hpp"

/** @file regularpolygon.hpp */

namespace blimp {
    
    //! A geometry, representing a regular polygon.
    class RegularPolygon : public blimp::Geometry {
        public:
            /** The default constructor.
             * Creates a regular polygon with the given parameters.
             * The polygon has a depth of 0 and is centered at the origin, with the first vertex at (0, radius).
             * Vertices are ordered counter-clockwise, forming triangles that all contain the first vertex.
             * The vertices array thus looks like [A1, A2, A3, A1, A3, A4, A1, A4, A5, ...], where A1..An are the edge vertices.
             * @param sides The number of sides of the polygon
             * @param radius The radius of the polygon
             * @param colors The colors of the polygon's vertices
            */
            RegularPolygon(int sides = 3, float radius = 0.5, ColorVector* colors = nullptr);
    };

}

#endif