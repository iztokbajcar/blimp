#ifndef _blimp_LIGHT
#define _blimp_LIGHT

#include "color.hpp"
#include "node.hpp"

/** @file light.hpp */

namespace blimp {

    //! Represents a light that illuminates objects.
    class Light: public blimp::Node {
        public:
            /** The default constructor.
             * Creates a white directional light with the intensity of `1.0`.
            */
            Light();

            /** Creates a light with the given color and intensity.
             * @param color The color of the light
             * @param intensity The intensity of the light
            */
            Light(Color color, float intensity);

            /** Returns the color of the light. 
             * @return The light's color
            */
            Color* getColor();

            /** Returns the intensity of the light.
             * @return The light's intensity
            */
            float getIntensity();

            /** Sets the color of the light.
             * @param color The new color of the light
            */
            void setColor(Color color);

            /** Sets the intensity of the light.
             * @param intensity The new intensity of the light
            */
            void setIntensity(float intensity);

        protected:
            blimp::Color color; /**< The light's color. */
            float intensity; /**< The light's intensity. */
    };

}

#endif