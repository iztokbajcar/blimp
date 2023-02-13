#ifndef _blimp_NODE
#define _blimp_NODE

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>

#include "geometry.hpp"
#include "material.hpp"

/** @file node.hpp */

namespace blimp {

    //! Represents anything that can be located in 3D space, including the scene.
    class Node {
        public:
            /** The default constructor. 
             * Creates a node with the identity transformation matrix (positioned at origin, no rotation, scale of 1).
            */
            Node();

            /** The default destructor. 
             * Deletes the node and the list of its child nodes.
            */
            ~Node();

            static const int NODE_TYPE_GROUP;  /**< Indicates that the node will function as a means of grouping objects. */
            static const int NODE_TYPE_MESH;  /**< Indicates that the node is a Mesh. */
            static const int NODE_TYPE_DIRECTIONAL_LIGHT;  /**< Indicates that the node is a DirectionalLight. */
            static const int NODE_TYPE_POINT_LIGHT;  /**< Indicates that the node is a PointLight. */
            static const int NODE_TYPE_SPOT_LIGHT;  /**< Indicates that the node is a SpotLight. */
            static const int NODE_TYPE_AMBIENT_LIGHT;  /**< Indicates that the node is an AmbientLight. */
            static const int NODE_TYPE_PERSPECTIVE_CAMERA;  /**< Indicates that the node is a PerspectiveCamera. */
            static const int NODE_TYPE_ORTHOGRAPHIC_CAMERA;  /**< Indicates that the node is an OrthographicCamera. */

            /** Returns the type of the node.
             * @return The node type, as defined by the NODE_TYPE_* constants.
            */
            int getNodeType();

            /** Returns the local transformation matrix of the node.
             * @return The node's local transformation matrix.
            */
            glm::mat4 getTransformationMatrix();

            /** Returns the node's global transformation matrix. 
             * The global transformation matrix is the product of the parent node's global transformation matrix and the node's local transformation matrix.
             * @return The node's global transformation matrix.
            */
            glm::mat4 getGlobalTransformationMatrix();

            /** Returns the transformation matrix of the parent node.
             * @return The transformation matrix of the parent node.
            */
            glm::mat4 getParentTransformationMatrix();

            /** Returns the translation of the node.
             * @return The local translation of the node.
            */
            glm::vec3 getTranslation();

            /** Returns the rotation of the node.
             * @return The local rotation of the node.
            */
            glm::quat getRotation();

            /** Returns the scale of the node.
             * @return The local scale of the node.
            */
            glm::vec3 getScale();

            /** Returns the node's facing direction.
             * @return The direction the node is facing, in world space.
            */
            glm::vec3 getForwardDirection();

            /** Returns the vector of child nodes.
             * @return A pointer to the vector of child nodes.
            */
            std::vector<Node*>* getChildren();

            /** Sets the transformation matrix of the parent node.
             * This is used internally in addChild, when a child node is added.
             * @param parentTransformationMatrix The transformation matrix of the parent node.
            */
            void setParentTransformationMatrix(glm::mat4 parentTransformationMatrix);

            /** Sets the translation of the node.
             * Translates the node relative to the origin.
             * @param x The translation along the x axis.
             * @param y The translation along the y axis.
             * @param z The translation along the z axis.
            */
            void setTranslation(float x, float y, float z);

            /** Sets the rotation of the node.
             * @param x The rotation around the x axis.
             * @param y The rotation around the y axis.
             * @param z The rotation around the z axis.
            */
            void setRotation(float x, float y, float z);

            /** Translates the node.
             * Translates the node relative to the current position.
             * @param x The translation along the x axis.
             * @param y The translation along the y axis.
             * @param z The translation along the z axis.
            */
            void translate(float x, float y, float z);

            /** Rotates the node.
             * Rotates the node relative to the current rotation.
             * @param x The rotation around the x axis.
             * @param y The rotation around the y axis.
             * @param z The rotation around the z axis.
            */
            void rotate(float x, float y, float z);

            /** Sets the scale of the node.
             * @param x The scale along the x axis.
             * @param y The scale along the y axis.
             * @param z The scale along the z axis.
            */
            void setScale(float x, float y, float z);

            /** Adds a child node to the node.
             * The child node's parent transformation matrix is set to the node's global transformation matrix.
             * @param child The child node to add.
            */
            void addChild(Node* child);

            /** Removes a child node from the node.
             * @param child The child node to remove.
            */
            void removeChild(Node* child);

            /** Returns the parent node.
             * @return A pointer to the parent node.
            */
            Node* getParent();

            /** Returns the vector of all descendant nodes.
             * This includes all child nodes and their children recursively.
             * @return A vector of pointers to the descendant nodes.
            */
            std::vector<Node*> traverseChildren();

        protected:
            int nodeType; /**< Specifies the node type; mainly used by Window to distinguish between different types of objects when rendering. */

        private:
            glm::vec3 translation;
            glm::quat rotation;
            glm::vec3 scale;

            Node* parent = nullptr;
            std::vector<Node*>* children;
            glm::mat4 parentTransformationMatrix;

            void setParent(Node* parent);
    };

}

#endif