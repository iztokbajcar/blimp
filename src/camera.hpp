#ifndef _blimp_CAMERA
#define _blimp_CAMERA

#include <glm/glm.hpp>

#include "node.hpp"

/** @file camera.hpp */

namespace blimp {
    
    //! A camera that can be used to render a scene.
    class Camera : public blimp::Node {
        public:
            /** The default constructor.
             * Creates a camera with the field of view of `60` degrees.
             */
            Camera();

            /** Returns the field of view of the camera.
             * @return The field of view, in degrees
             */
            float getFov();

            /** Returns the camera's view matrix.
             * @return The view matrix
             */
            virtual glm::mat4 getViewMatrix() = 0;

            /** Returns the camera's projection matrix.
             * @return The projection matrix
             */
            virtual glm::mat4 getProjectionMatrix() = 0;

            /** Sets the field of view of the camera.
             * @param fov The new field of view, in degrees
             */
            void setFov(float fov);

            /** Sets the camera's view matrix.
             * @param viewMatrix The new view matrix
             */
            void setViewMatrix(glm::mat4 viewMatrix);
        protected:
            float fov;  /**< The field of view of the camera, in degrees. */
    };

}

#endif