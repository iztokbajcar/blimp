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
            glm::mat4* getTransformationMatrix();
            glm::vec3 getTranslation();
            // glm::vec3 getRotation();  // TODO
            glm::vec3 getScale();
            void setTranslation(float x, float y, float z);
            // void setRotation(float x, float y, float z);  // TODO
            void setScale(float x, float y, float z);
            void addChild(Node* child);
            void removeChild(Node* child);

        private:
            std::vector<Node*>* children = nullptr;
            glm::mat4* transformationMatrix = nullptr;
    };

}

#endif