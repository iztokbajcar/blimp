#ifndef _blimp_TEXTURE
#define _blimp_TEXTURE

#include "textureoptions.hpp"

/** @file texture.hpp */

namespace blimp {

    //! Represents a texture that can be applied to a Texturable.
    class Texture {
        public:
            static const int TEXTURE_TYPE_2D;  /**< Indicates that the texture is a 2D texture. */
            static const int TEXTURE_TYPE_CUBEMAP;  /**< Indicates that the texture is a cubemap. */

            /** The default constructor.
             * Creates a texture with the default options.
            */
            Texture();

            int getTextureType();  /**< Returns the type of the texture. */
        protected:
            int textureType;  /**< The type of the texture, as defined by the TEXTURE_TYPE_* constants. */
    };

}

#endif