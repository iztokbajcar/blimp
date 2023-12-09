#ifndef _blimp_CUBEMAP
#define _blimp_CUBEMAP

#include "texture.hpp"
#include "texture2d.hpp"

/** @file cubemap.hpp */

namespace blimp {
    
    //! A cubemap
    class Cubemap : public blimp::Texture {
        public:
            /** The Cubemap constructor.
             * Creates a cubemap from six image files with the given filenames.
             * @param px The filename of the image file for the positive x face
             * @param nx The filename of the image file for the negative x face
             * @param py The filename of the image file for the positive y face
             * @param ny The filename of the image file for the negative y face
             * @param pz The filename of the image file for the positive z face
             * @param nz The filename of the image file for the negative z face
            */
            Cubemap(Texture2D* px, Texture2D* nx, Texture2D* py, Texture2D* ny, Texture2D* pz, Texture2D* nz);

            Texture2D* getPX();  /**< Returns the texture for the positive x face */
            Texture2D* getNX();  /**< Returns the texture for the negative x face */
            Texture2D* getPY();  /**< Returns the texture for the positive y face */
            Texture2D* getNY();  /**< Returns the texture for the negative y face */
            Texture2D* getPZ();  /**< Returns the texture for the positive z face */
            Texture2D* getNZ();  /**< Returns the texture for the negative z face */
        
        protected:
            Texture2D* px;  /**< The texture for the positive x face */
            Texture2D* nx;  /**< The texture for the negative x face */
            Texture2D* py;  /**< The texture for the positive y face */
            Texture2D* ny;  /**< The texture for the negative y face */
            Texture2D* pz;  /**< The texture for the positive z face */
            Texture2D* nz;  /**< The texture for the negative z face */
    };

}

#endif