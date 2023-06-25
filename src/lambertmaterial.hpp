#ifndef _blimp_LAMBERT_MATERIAL
#define _blimp_LAMBERT_MATERIAL

#include "material.hpp"

/** @file lambertmaterial.hpp */

namespace blimp {

    //! A material that uses the Lambertian reflectance model.
    class LambertMaterial : public blimp::Material {
        public:
            /** The default constructor.
             * Creates a Lambert material with the default shaders.
             * It will take into account all AmbientLight, DirectionalLight, PointLight and SpotLight objects in the scene.
             */
            LambertMaterial();

        private:
            static VertexShader defaultVertexShader;
            static FragmentShader defaultFragmentShader;
    };

}

#endif