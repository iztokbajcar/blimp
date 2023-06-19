#ifndef _blimp_TEXTURE_OPTIONS
#define _blimp_TEXTURE_OPTIONS

#include <GL/glew.h>

/** @file textureoptions.hpp */

namespace blimp {

    //! Options for a texture.
    class TextureOptions {
        public:
            //! Enumerates the possible wrap modes.
            enum WrapMode {
                REPEAT = GL_REPEAT,  /**< Repeat the texture */
                MIRROR = GL_MIRRORED_REPEAT,  /**< Repeat the texture with mirroring */
                CLAMP_EDGE = GL_CLAMP_TO_EDGE,  /**< Clamp the texture to the edge */
                CLAMP_BORDER = GL_CLAMP_TO_BORDER  /**< Clamp the texture to the border */
            };

            //! Enumerates the possible filter modes.
            enum FilterMode {
                NEAREST = GL_NEAREST,  /**< Use nearest neighbor interpolation */
                LINEAR = GL_LINEAR,  /**< Use linear interpolation */
                NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,  /**< Use nearest neighbor interpolation for the texture and nearest neighbor interpolation for the mipmap */
                LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,  /**< Use linear interpolation for the texture and nearest neighbor interpolation for the mipmap */
                NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,  /**< Use nearest neighbor interpolation for the texture and linear interpolation for the mipmap */
                LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR  /**< Use linear interpolation for the texture and linear interpolation for the mipmap */
            };

            /** The default constructor.
             * Creates a texture options object with the default options:
             * - all offsets: 0
             * - all wrap modes: REPEAT
             * - filter mode: LINEAR
            */
            TextureOptions();

            /** Creates a texture options object, setting every offset to the respective given offset and leaving the wrap modes at their default values.
             * @param offsetS The offset to use for the S coordinate
             * @param offsetT The offset to use for the T coordinate
            */
            TextureOptions(int offsetS, int offsetT);

            /** Creates a texture options object, setting all wrap modes to the given wrap mode and leaving the filter modes at their default values.
             * @param wrapMode The wrap mode to use
            */
            TextureOptions(WrapMode wrapMode);

            /** Creates a texture options object, setting both filter modes to the given filter mode and leaving wrap modes at their default values.
             * @param filterMode The filter mode to use
            */
            TextureOptions(FilterMode filterMode);

            /** Creates a texture options object, setting all wrap modes to the given wrap mode and both filter modes to the given filter mode.
             * @param wrapMode The wrap mode to use
             * @param filterMode The filter mode to use
            */
            TextureOptions(WrapMode wrapMode, FilterMode filterMode);

            /** Creates a texture options object, setting both wrap modes to the respective given wrap modes and both filter modes to the respective given filter mode.
             * @param wrapModeS The wrap mode to use for the S coordinate
             * @param wrapModeT The wrap mode to use for the T coordinate
             * @param minFilterMode The filter mode to use for the minification filter
             * @param magFilterMode The filter mode to use for the magnification filter
            */
            TextureOptions(WrapMode wrapModeS, WrapMode wrapModeT, FilterMode minFilterMode, FilterMode magFilterMode);

            /** Sets the wrap mode across all axes to the given wrap mode.
             * @param wrapMode The wrap mode to use
            */
            void setWrapMode(WrapMode wrapMode);

            /** Sets the wrap modes across the respective axes.
             * @param wrapModeS The wrap mode to use for the S coordinate
             * @param wrapModeT The wrap mode to use for the T coordinate
            */
            void setWrapModes(WrapMode wrapModeS, WrapMode wrapModeT); 

            /** Sets the wrap mode across the S axis.
             * @param wrapModeS The wrap mode to use for the S coordinate
            */
            void setWrapModeS(WrapMode wrapModeS);

            /** Sets the wrap mode across the T axis.
             * @param wrapModeT The wrap mode to use for the T coordinate
            */
            void setWrapModeT(WrapMode wrapModeT);

            /** Sets the filter mode across both axes to the given filter mode.
             * @param filterMode The filter mode to use
            */
            void setFilterMode(FilterMode filterMode);

            /** Sets the filter modes to the respective given filter modes.
             * @param minFilterMode The filter mode to use for the minification filter
             * @param magFilterMode The filter mode to use for the magnification filter
            */
            void setFilterModes(FilterMode minFilterMode, FilterMode magFilterMode);

            /** Sets the minifying filter mode.
             * @param minFilterMode The filter mode to use for the minification filter
            */
            void setMinFilterMode(FilterMode minFilterMode);

            /** Sets the magnification filter mode.
             * @param magFilterMode The filter mode to use for the magnification filter
            */
            void setMagFilterMode(FilterMode magFilterMode);

            /** Returns the wrap mode across the S axis.
             * @return The wrap mode across the S axis
            */
            WrapMode getWrapModeS();

            /** Returns the wrap mode across the T axis.
             * @return The wrap mode across the T axis
            */
            WrapMode getWrapModeT();

            /** Returns the minifying filter mode.
             * @return The minifying filter mode
            */
            FilterMode getMinFilterMode();

            /** Returns the magnifying filter mode.
             * @return The magnifying filter mode
            */
            FilterMode getMagFilterMode();
            
        private:
            WrapMode wrapS;
            WrapMode wrapT;
            FilterMode minFilterMode;
            FilterMode magFilterMode;
    };

}

#endif