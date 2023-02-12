#ifndef _blimp_PHONG_MATERIAL
#define _blimp_PHONG_MATERIAL

#include "material.hpp"

/** @file phongmaterial.hpp */

namespace blimp {

    //! A material that uses the Phong reflectance model.
    class PhongMaterial : public blimp::Material {
        public:
            /** The default constructor.
             * Creates a Phong material with the default shaders.
             * It will take into account all AmbientLight, DirectionalLight, PointLight and SpotLight objects in the scene.
             */
            PhongMaterial();
    };

}

#endif