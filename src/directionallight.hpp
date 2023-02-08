#ifndef _blimp_DIRECTIONAL_LIGHT
#define _blimp_DIRECTIONAL_LIGHT

#include "light.hpp"

namespace blimp {

    class DirectionalLight : public blimp::Light {
        public:
            DirectionalLight();
            DirectionalLight(blimp::Color color, float intensity);
    };

}

#endif