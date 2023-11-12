#ifndef _blimp_SCENE
#define _blimp_SCENE

#include "node.hpp"
#include "texturable.hpp"

/** @file scene.hpp */

namespace blimp {

    class Scene: public blimp::Node, public blimp::Texturable {
        public:
            Scene();
    };

}

#endif