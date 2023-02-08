#ifndef _blimp_AMBIENT_LIGHT
#define _blimp_AMBIENT_LIGHT

#include "light.hpp"

namespace blimp {

    class AmbientLight : public blimp::Light {
        public:
            AmbientLight();
            AmbientLight(blimp::Color color, float intensity);
    };

}

#endif