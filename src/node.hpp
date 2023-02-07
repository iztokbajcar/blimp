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
            Node();
            Node(Geometry* geometry, Material* material);
            ~Node();

            static const int NODE_TYPE_NODE = 0;
            static const int NODE_TYPE_DIRECTIONAL_LIGHT = 1;
            static const int NODE_TYPE_POINT_LIGHT = 2;
            static const int NODE_TYPE_SPOT_LIGHT = 3;

            int getType();
            glm::mat4 getTransformationMatrix();
            glm::mat4 getGlobalTransformationMatrix();
            glm::mat4 getParentTransformationMatrix();
            glm::vec3 getTranslation();
            glm::quat getRotation();
            glm::vec3 getScale();
            glm::vec3 getForwardDirection();  // get the direction the node is facing, in world space
            std::vector<Node*>* getChildren();
            Geometry* getGeometry();
            Material* getMaterial();
            void setParentTransformationMatrix(glm::mat4 parentTransformationMatrix);
            void setTranslation(float x, float y, float z);
            void setRotation(float x, float y, float z);
            void translate(float x, float y, float z);
            void rotate(float x, float y, float z);
            void setScale(float x, float y, float z);
            void addChild(Node* child);
            void removeChild(Node* child);
            std::vector<Node*> traverseChildren();

        protected:
            int nodeType = NODE_TYPE_NODE;

        private:
            Geometry* geometry = nullptr;
            Material* material = nullptr;

            glm::vec3 translation;
            glm::quat rotation;
            glm::vec3 scale;

            std::vector<Node*>* children;
            glm::mat4 parentTransformationMatrix;
    };

}

#endif