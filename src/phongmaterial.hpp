#ifndef _blimp_PHONG_MATERIAL
#define _blimp_PHONG_MATERIAL

#include "material.hpp"

/** @file phongmaterial.hpp */

namespace blimp {

    //! A material that uses the Phong reflectance model.
    /**
     * It will take into account all AmbientLight, DirectionalLight, PointLight and SpotLight objects in the scene.
     */
    class PhongMaterial : public blimp::Material {
        public:
            /** The default constructor.
             * Creates a Phong material with the default shaders, a shininess of `32.0` and a specular factor of `0.75`.
             */
            PhongMaterial();

            /** Creates a Phong material with the given shininess and specular factor.
             * @param shininess The shininess of the material
             * @param specular The specular factor of the material. It determines how much impact the specular component of the calculated light color will have on the final color.
             */
            PhongMaterial(float shininess, float specular);

            /** Returns the material's shininess. 
             * @return The material's shininess
            */
            float getShininess();

            /** Sets the material's shininess.
             * @param shininess The new shininess of the material.
            */
            void setShininess(float shininess);

            /** Returns the specular factor. 
             * @return The specular factor
            */
            float getSpecular();

            /** Sets the specular factor.
             * @param specular The new specular factor.
            */
            void setSpecular(float specular);

        protected:
            float shininess;  /**< The material's shininess. */
            float specular;  /**< The specular factor. */
        
        private:
            class PhongMaterialVertexShader : public VertexShader {
                public:
                    PhongMaterialVertexShader();
                    PhongMaterialVertexShader(std::vector<ShaderFeature> shaderFeatures);
                
                protected:
                    std::string generateAbout();
            };

            class PhongMaterialFragmentShader : public FragmentShader {
                public:
                    PhongMaterialFragmentShader();
                    PhongMaterialFragmentShader(std::vector<ShaderFeature> shaderFeatures);

                protected:
                    std::string generateAbout();
                    std::string generateGlobals();
                    std::string generateMain();

                private:
                    float shininess;
                    float specular;
                    std::string generateMain(float shininess, float specular);
            };

            static PhongMaterialVertexShader defaultVertexShader;
            static PhongMaterialFragmentShader defaultFragmentShader;
            
    };

}

#endif