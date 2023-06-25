#ifndef _blimp_FRAGMENT_SHADER
#define _blimp_FRAGMENT_SHADER

#include "shader.hpp"

/** @file fragmentshader.hpp */

namespace blimp {

    //! A fragment shader.
    class FragmentShader : public Shader {
        public:
            /** The default constructor. */
            FragmentShader();

            /** Creates the shader and registers the given features. */
            FragmentShader(std::vector<ShaderFeature> shaderFeatures);     

        protected:
            std::string generateDefines();
            std::string generateUniforms();
            std::string generateGlobals();
            std::string generateIns();
            std::string generateOuts();
            std::string generateMain();
    };

}

#endif