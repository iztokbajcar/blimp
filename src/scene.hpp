#ifndef _blimp_SCENE
#define _blimp_SCENE

#include "node.hpp"
#include "texturable.hpp"

/** @file scene.hpp */

namespace blimp {
    //! A special textureable node, representing the root node of a scene.
    class Scene: public blimp::Node, public blimp::Texturable {
        public:
            Scene();
    };

}

#endif