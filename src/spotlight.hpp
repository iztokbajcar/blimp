#ifndef _blimp_SPOT_LIGHT
#define _blimp_SPOT_LIGHT

#include "light.hpp"

namespace blimp {

    class SpotLight : public blimp::Light {
        public:
            SpotLight();
            SpotLight(blimp::Color color, float intensity, float inner, float outer);
            float getInnerCutoff();
            float getOuterCutoff();
            void setInnerCutoff(float inner);
            void setOuterCutoff(float outer);

        protected:
            float inner;
            float outer;
    };

}

#endif