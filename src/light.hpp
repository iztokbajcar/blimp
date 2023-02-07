#ifndef _blimp_LIGHT
#define _blimp_LIGHT

#include "color.hpp"
#include "node.hpp"

namespace blimp {

    class Light: public blimp::Node {
        public:
            Light();

        protected:
            blimp::Color color;
            float intensity;
    };

}

#endif