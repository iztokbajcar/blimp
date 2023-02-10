#ifndef _blimp_POINT_LIGHT
#define _blimp_POINT_LIGHT

#include "light.hpp"

namespace blimp {

    class PointLight : public blimp::Light {
        public:
            PointLight();
            PointLight(blimp::Color color, float intensity, float attenuation);
            float getAttenuation();
            void setAttenuation(float attenuation);

        protected:
            float attenuation;
    };

}

#endif