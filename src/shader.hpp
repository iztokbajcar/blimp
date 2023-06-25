#ifndef _blimp_SHADER
#define _blimp_SHADER

#include <GL/glew.h>
#include <string>
#include <vector>

#include "shaderfeature.hpp"

/** @file shader.hpp **/

namespace blimp {

    //! A class, representing a shader.
    class Shader {
        public:
            //! An enum of types of shaders.
            enum ShaderType {
                VERTEX      = GL_VERTEX_SHADER,  /**< A vertex shader */
                FRAGMENT    = GL_FRAGMENT_SHADER  /**< A fragment shader */
            };

            /** The default constructor. */
            Shader();

            /** Creates the shader and registers the given features. */
            Shader(std::vector<ShaderFeature> shaderFeatures);

            /** Generates the source code for the shader and returns a pointer to it. */
            std::string* generateSource();

        protected:
            std::string source;  /**< The source code of the shader. */
            ShaderType type;  /**< The type of the shader (e.g. vertex, fragment, ...). */

            /** Generates the "about" section of the shader. 
             * It will be generated at the very beginning of the shades's source code and should only contain comments.
            */
            virtual std::string generateAbout();

            /** Generates the "version" tag of the shader, e.g. `#version 330 core`. */
            std::string generateVersionTag();

            /** Generates the "defines" section of the shader. 
             * It will be generated after the "about" section and should only contain `#define` statements and other standalone declarations.
            */
            virtual std::string generateDefines();

            /** Generates the uniforms section, where all uniforms should be declared. */
            virtual std::string generateUniforms();

            /** Generates the global variables section, where all global variables and functions (which can reference previously defined values) should be declared. */
            virtual std::string generateGlobals();

            /** Generates the "in" variables section, where all input variables (attributes) should be declared. */
            virtual std::string generateIns();

            /** Generates the "out" variables section, where all output variables (varyings, outputs) should be declared. */
            virtual std::string generateOuts();

            /** Generates the main function of the shader. */
            virtual std::string generateMain();

            bool usesPosition;  /**< Whether the shader uses the position of the vertex. */
            bool usesCameraPosition;  /**< Whether the shader uses the position of the camera. */
            bool usesColor;   /**< Whether the shader uses the color of the vertex. */
            bool usesNormals;  /**< Whether the shader uses the normals of the vertex. */
            bool usesLights;  /**< Whether the shader uses lights. */
            bool usesTextures;  /**< Whether the shader uses textures. */
    };

}

#endif