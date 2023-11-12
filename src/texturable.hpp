#ifndef _blimp_TEXTURABLE
#define _blimp_TEXTURABLE

#include "texture.hpp"

/** @file texturable.hpp */

namespace blimp {

    //! Represents anrything that a texture may be applied to.
    class Texturable {
        public:
            /** The default constructor.
             * Creates a texturable object without a texture.
            */ 
            Texturable();

            /** Gets the texturable's texture.
             * @return The texturable's texture
             */
            Texture* getTexture();

            /** Sets the texturable's texture.
             * @param texture The texturable's texture
             */
            void setTexture(Texture* texture);

            /** Sets the texturable's texture, using the provided options.
             * @param texture The texturable's texture
             * @param options The texture options
             */
            void setTexture(Texture* texture, TextureOptions* options);

            /** Returns a pointer to the texture options object.
             * @return The pointer to the texture options object
            */
            TextureOptions* getTextureOptions();

            /** Sets the texture options object.
             * @param options A pointer to the new texture options object
            */
            void setTextureOptions(TextureOptions* options);

        protected:
            Texture* texture = nullptr;  /**< The texture. **/
            TextureOptions* texOptions = nullptr;  /**< The texture options. **/
            static TextureOptions defaultTexOptions;  /**< The default texture options. **/

        private:
            bool usingDefaultTexOptions;
    };

}

#endif