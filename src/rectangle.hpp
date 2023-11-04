#ifndef _blimp_RECTANGLE
#define _blimp_RECTANGLE

#include "geometry.hpp"

/** @file rectangle.hpp */

namespace blimp {
    
    //! A rectangle in 3D space.
    class Rectangle : public Geometry {
        public:
            /** The default constructor. 
             * Creates a rectangle with the specified width and height.
            */
            Rectangle(float width = 1.0f, float height = 1.0f, ColorVector* colors = nullptr);
    };

}

#endif