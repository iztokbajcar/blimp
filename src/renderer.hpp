#ifndef _blimp_RENDERER
#define _blimp_RENDERER

#include "camera.hpp"
#include "node.hpp"

namespace blimp {

    class Renderer {
        public:
            Renderer();
            void render(Node scene, Camera camera);
    };

}

#endif