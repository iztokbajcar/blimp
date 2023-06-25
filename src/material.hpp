#ifndef _blimp_MATERIAL
#define _blimp_MATERIAL

#include <GL/glew.h>
#include <string>
#include <vector>

#include "fragmentshader.hpp"
#include "texture.hpp"
#include "vertexshader.hpp"

/** @file material.hpp */

namespace blimp {

    //! A material that defines how a mesh is rendered.
    class Material {
        public:
            /** The default constructor.
             * Creates a material with the default shaders.
             * It will render the mesh with its vertices' colors, interpolating them to the fragments.
             * It will not take lights into account, 
            */
            Material();

            /** Creates a material with the given shaders.
             * @param vertexShader The vertex shader
             * @param fragmentShader The fragment shader
            */
            Material(VertexShader* vertexShader, FragmentShader* fragmentShader);

            /** Returns the material's vertex shader.
             * @return The material's vertex shader
            */
            VertexShader* getVertexShader();

            /** Returns the material's fragment shader.
             * @return The material's fragment shader
            */
            FragmentShader* getFragmentShader();

            /** Determines if the material was set to use lights.
             * This is used by Window to determine if it should pass lighting data to the material when rendering.
             * @return `true` if the material uses lights, `false` otherwise
            */
            bool usesLights();

            /** Sets the material to use lights.
             * For materials that don't use lighting from the scene, this should be set to false to speed up the rendering process.
             * @param usesLights `true` if the material should use lights, `false` otherwise
            */
            void setUsesLights(bool usesLights);

            //! @todo allow custom ambient, diffuse and specular colors

        protected:
            VertexShader* vertexShader;  /**< The material's vertex shader source. */
            FragmentShader* fragmentShader;  /**< The material's fragment shader source. */
            GLuint program;  /**< The ID of the material's shader program. Should not be set manually as it will be determined automatically by Window when compiling the material's shaders. */
            bool lights = false;  /**< `true` if the material uses lights, `false` otherwise. */

        private:
            static VertexShader defaultVertexShader;
            static FragmentShader defaultFragmentShader;
    };


}

#endif