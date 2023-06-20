#ifndef _blimp_TEXTURE
#define _blimp_TEXTURE

#include <SOIL/SOIL.h>
#include <string>

#include "textureoptions.hpp"

/** @file texture.hpp */

namespace blimp {

    //! A texture that can be applied to a mesh.
    //! @todo Add support for 3D textures and rename this to Texture2D
    class Texture {
        public:
            /** The default constructor.
             * Creates a texture from an image file with the given filename.
             * @param filename The filename of the image file
            */
            Texture(std::string filename);

            //! @todo Add support for creating textures from raw data

            /** Returns the width of the texture.
             * @return The width of the texture
            */
            int getWidth();

            /** Returns the height of the texture.
             * @return The height of the texture
            */
            int getHeight();

            /** Returns the data of the texture as a char array.
             * @return The data of the texture
            */
            unsigned char* getData();
            
        protected:
            int width;
            int height;

        private:
            TextureOptions* options;
            unsigned char* data;
    };

}

#endif