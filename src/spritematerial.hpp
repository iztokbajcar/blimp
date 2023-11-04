#ifndef _blimp_SPRITE_MATERIAL
#define _blimp_SPRITE_MATERIAL

#include "material.hpp"

/** @file spritematerial.hpp */

namespace blimp {

    //! A material for rendering (billboarded) sprites.
    class SpriteMaterial : public blimp::Material {
        public:
            /** The default constructor.
             * Creates a sprite material with the default shaders. 
            */
            SpriteMaterial();

        private:
            class SpriteMaterialVertexShader : public VertexShader {
                public:
                    SpriteMaterialVertexShader();
                    SpriteMaterialVertexShader(std::vector<ShaderFeature> shaderFeatures);

                protected:
                    std::string generateAbout();
                    std::string generateMain();
            };

            class SpriteMaterialFragmentShader : public FragmentShader {
                public:
                    SpriteMaterialFragmentShader();
                    SpriteMaterialFragmentShader(std::vector<ShaderFeature> shaderFeatures);

                protected:
                    std::string generateAbout();
                    std::string generateMain();
            };

            static SpriteMaterialVertexShader defaultVertexShader;
            static SpriteMaterialFragmentShader defaultFragmentShader;
    };

}

#endif