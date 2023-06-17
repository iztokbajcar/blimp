#ifndef _blimp_TEXTURE
#define _blimp_TEXTURE

#include <SOIL/SOIL.h>
#include <string>

/** @file image.hpp */

namespace blimp {

    //! A texture that can be applied to a mesh.
    class Texture {
        public:
            /** The default constructor.
             * Creates a texture from an image file with the given filename.
             * @param filename The filename of the image file
            */
            Texture(std::string filename);

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
            unsigned char* data;
    };

}

#endif