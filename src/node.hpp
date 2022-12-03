#ifndef _blimp_NODE
#define _blimp_NODE

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "geometry.hpp"

namespace blimp {

    class Node {
        public:
            Node();
            blimp::Geometry* geometry = nullptr;

        private:
            std::vector<Node>* children = nullptr;
            glm::mat4* transformationMatrix = nullptr;
    };

}

#endif