#ifndef _blimp_AMBIENT_LIGHT
#define _blimp_AMBIENT_LIGHT

#include "light.hpp"

/** @file ambientlight.hpp */

namespace blimp {

    //! A light that illuminates all objects in the scene equally.
    class AmbientLight : public blimp::Light {
        public:
            /** The default constructor.
             * Creates a white ambient light with the intensity of `1.0`.
            */
            AmbientLight();

            /** Creates an ambient light with the given color and intensity.
             * @param color The color of the light
             * @param intensity The intensity of the light
            */
            AmbientLight(blimp::Color color, float intensity);
    };

}

#endif