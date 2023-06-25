#include "lambertmaterial.hpp"

blimp::VertexShader blimp::LambertMaterial::defaultVertexShader = VertexShader(
     std::vector<ShaderFeature> {
          ShaderFeature::USES_POSITION,
          ShaderFeature::USES_COLOR,
          ShaderFeature::USES_LIGHTS,
          ShaderFeature::USES_TEXTURES,
     }
);

blimp::FragmentShader blimp::LambertMaterial::defaultFragmentShader = FragmentShader(
     std::vector<ShaderFeature> {
          ShaderFeature::USES_POSITION,
          ShaderFeature::USES_COLOR,
          ShaderFeature::USES_LIGHTS,
          ShaderFeature::USES_TEXTURES,
     }
);

blimp::LambertMaterial::LambertMaterial() {
     this -> vertexShader = &blimp::LambertMaterial::defaultVertexShader;
     this -> fragmentShader = &blimp::LambertMaterial::defaultFragmentShader;
     
     this -> lights = true;
}