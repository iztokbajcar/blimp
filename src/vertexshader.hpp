#ifndef _blimp_VERTEX_SHADER
#define _blimp_VERTEX_SHADER

#include <string>

#include "shader.hpp"

/** @file vertexshader.hpp */

namespace blimp {

    //! A vertex shader.
    class VertexShader : public Shader {
        public:
            /** The default constructor. */
            VertexShader();

            /** Creates the shader and registers the given features. */
            VertexShader(std::vector<ShaderFeature> shaderFeatures);     

        protected:
            std::string generateDefines();
            std::string generateGlobals();
            std::string generateUniforms();
            std::string generateIns();
            std::string generateOuts();
            std::string generateMain();
    };

}

#endif