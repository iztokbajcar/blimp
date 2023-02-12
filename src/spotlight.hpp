#ifndef _blimp_SPOT_LIGHT
#define _blimp_SPOT_LIGHT

#include "light.hpp"

/** @file spotlight.hpp */

namespace blimp {

    //! A light that illuminates from a single point in a specific direction in a cone.
    class SpotLight : public blimp::Light {
        public:
            /** The default constructor.
             * Creates a white spot light with the intensity of `1.0`, an inner cutoff of `0.9` and an outer cutoff of `0.85`.
            */
            SpotLight();

            /** Creates a spot light with the given color, intensity, inner cutoff and outer cutoff.
             * @param color The color of the light
             * @param intensity The intensity of the light
             * @param inner The inner cutoff of the light
             * @param outer The outer cutoff of the light
            */
            SpotLight(blimp::Color color, float intensity, float inner, float outer);

            /** Returns the inner cutoff of the light. 
             * @return The light's inner cutoff
            */
            float getInnerCutoff();

            /** Returns the outer cutoff of the light. 
             * @return The light's outer cutoff
            */
            float getOuterCutoff();

            /** Sets the inner cutoff of the light.
             * Looking from the center of the lit circle outwards, this is where the intensity starts to fade out.
             * As it represents the cosine of the angle at which this happens and not the angle itself, the inner cutoff should actually be bigger than the outer cutoff to achieve the (most likely) desired result.
             * @param inner The cosine of the new inner cutoff of the light
            */
            void setInnerCutoff(float inner);

            /** Sets the outer cutoff of the light.
             * Looking from the center of the lit circle outwards, this is where the intensity is completely faded out.
             * As it represents the cosine of the angle at which this happens and not the angle itself, the outer cutoff should actually be smaller than the inner cutoff to achieve the (most likely) desired result.
             * @param outer The cosine of the new outer cutoff of the light
            */
            void setOuterCutoff(float outer);
        protected:
            float inner;  /**< Cosine of the light's inner cutoff. */
            float outer;  /**< Cosine of the light's outer cutoff. */
    };

}

#endif