#ifndef _blimp_DIRECTIONAL_LIGHT
#define _blimp_DIRECTIONAL_LIGHT

#include "light.hpp"

/** @file directionallight.hpp */

namespace blimp {

    //! A light that illuminates from the same direction everywhere in the scene.
    class DirectionalLight : public blimp::Light {
        public:
            /** The default constructor.
             * Creates a white directional light with the intensity of `1.0`.
            */
            DirectionalLight();

            /** Creates a directional light with the given color and intensity.
             * @param color The color of the light
             * @param intensity The intensity of the light
            */
            DirectionalLight(blimp::Color color, float intensity);
    };

}

#endif