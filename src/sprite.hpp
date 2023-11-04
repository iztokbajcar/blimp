#ifndef _blimp_SPRITE
#define _blimp_SPRITE

#include "mesh.hpp"
#include "rectangle.hpp"

/** @file sprite.hpp */

namespace blimp {

    //! Represents a 2D mesh in 3D space, facing the camera.
    class Sprite : public Mesh {
        public:
            /** The default constructor.
             * Creates a 1x1 rectangle sprite.   
            */
            Sprite();

            /** 
             * Creates a sprite with the specified geometry.
             * @param geometry The sprite geometry
             * @param material The sprite material
            */
            Sprite(Geometry* geometry, Material* material);

        private:
            static Rectangle defaultGeometry;
            static Material defaultMaterial;
            float width;
            float height;

    };

}

#endif