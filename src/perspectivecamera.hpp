#ifndef _blimp_PERSPECTIVE_CAMERA
#define _blimp_PERSPECTIVE_CAMERA

#include "camera.hpp"

/** @file perspectivecamera.hpp */

namespace blimp {

    //! Represents a perspective camera.
    class PerspectiveCamera : public blimp::Camera {
        public:
            /** Creates a perspective camera with the given field of view, aspect ratio, near plane, and far plane.
             * @param fov The field of view of the camera, in degrees
             * @param aspect The aspect ratio of the camera
             * @param near The distance to the near plane
             * @param far The distance to the far plane
             */
            PerspectiveCamera(float fov, float aspect, float near, float far);

            /** Returns the field of view of the camera.
             * @return The field of view, in degrees
             */
            float getFov();

            /** Returns the aspect ratio of the camera.
             * @return The aspect ratio
             */
            float getAspect();

            /** Returns the distance to the near plane.
             * @return The distance to the near plane
             */
            float getNear();

            /** Returns the distance to the far plane.
             * @return The distance to the far plane
             */
            float getFar();

            /** Sets the field of view of the camera.
             * @param fov The new field of view, in degrees
             */
            void setFov(float fov);

            /** Sets the aspect ratio of the camera.
             * @param aspect The new aspect ratio
             */
            void setAspect(float aspect);

            /** Sets the distance to the near plane.
             * @param near The new distance to the near plane
             */
            void setNear(float near);

            /** Sets the distance to the far plane.
             * @param far The new distance to the far plane
             */
            void setFar(float far);

            /** Returns the camera's view matrix.
             * @return The view matrix
             */
            glm::mat4 getViewMatrix();

            /** Returns the camera's projection matrix.
             * @return The projection matrix
             */
            glm::mat4 getProjectionMatrix();

        private:
            float fov;
            float aspect;
            float near;
            float far;
    };
    
}

#endif