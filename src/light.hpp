#ifndef _blimp_LIGHT
#define _blimp_LIGHT

#include "color.hpp"
#include "node.hpp"

namespace blimp {

    class Light: public blimp::Node {
        public:
            Light();
            Light(Color color, float intensity);
            Color* getColor();
            float getIntensity();
            void setColor(Color color);
            void setIntensity(float intensity);

        protected:
            blimp::Color color;
            float intensity;
    };

}

#endif