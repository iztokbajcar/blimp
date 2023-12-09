#ifndef _blimp_TEXTURE2D
#define _blimp_TEXTURE2D

#include <SOIL/SOIL.h>
#include <string>

#include "texture.hpp"

/** @file texture2d.hpp */

namespace blimp {

    //! A 2D texture.
    class Texture2D : public blimp::Texture {
        public:
            /** The default constructor.
             * Creates a texture from an image file with the given filename.
             * @param filename The filename of the image file
            */
            Texture2D(std::string filename);

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

        private:
            int width;
            int height;
            TextureOptions* options;
            unsigned char* data;
    };

}

#endif