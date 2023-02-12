#ifndef _blimp_POINT_LIGHT
#define _blimp_POINT_LIGHT

#include "light.hpp"

/** @file pointlight.hpp */

namespace blimp {

    //! A light that illuminates from a single point in the scene.
    /**
     * Its intensity decreases with the square of distance from the source.
     */
    class PointLight : public blimp::Light {
        public:
            /** The default constructor.
             * Creates a white point light with the intensity of `1.0` and an attenuation of `1.0`.
            */
            PointLight();

            /** Creates a point light with the given color, intensity and attenuation.
             * @param color The color of the light
             * @param intensity The intensity of the light
             * @param attenuation The attenuation of the light
            */
            PointLight(blimp::Color color, float intensity, float attenuation);

            /** Returns the attenuation of the light. 
             * @return The light's attenuation
            */
            float getAttenuation();

            /** Sets the attenuation of the light.
             * @param attenuation The new attenuation of the light
            */
            void setAttenuation(float attenuation);

        protected:
            float attenuation;  /**< The light's attenuation. */
    };

}

#endif