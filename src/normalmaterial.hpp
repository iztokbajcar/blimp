#ifndef _blimp_NORMAL_MATERIAL
#define _blimp_NORMAL_MATERIAL

#include "material.hpp"

/** @file normalmaterial.hpp */

namespace blimp {

    //! A material, colored based on the directions of the mesh's normals.
    class NormalMaterial : public blimp::Material {
        public:
            /** The default constructor.
             * Creates a normal material with the default shaders.
             * It will ignore all color data and will instead color the mesh based on the directions of the mesh's geometry's normals.
             */
            NormalMaterial();
    };

}

#endif