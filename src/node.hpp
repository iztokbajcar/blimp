#ifndef _blimp_NODE
#define _blimp_NODE

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

#include "geometry.hpp"
#include "material.hpp"

namespace blimp {

    class Node {
        public:
            Node(Geometry* geometry, Material* material);

            glm::mat4 getTransformationMatrix();
            glm::vec3 getTranslation();
            glm::quat getRotation();
            glm::vec3 getScale();
            std::vector<Node*>* getChildren();
            void setTranslation(float x, float y, float z);
            void setRotation(float x, float y, float z);
            void setScale(float x, float y, float z);
            void addChild(Node* child);
            void removeChild(Node* child);

        private:
            Geometry* geometry = nullptr;
            Material* material = nullptr;

            glm::vec3 translation;
            glm::quat rotation;
            glm::vec3 scale;

            std::vector<Node*> children;
            // glm::mat4* transformationMatrix = nullptr;
    };

}

#endif