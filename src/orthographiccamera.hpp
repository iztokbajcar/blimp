#ifndef _blimp_ORTHOGRAPHIC_CAMERA
#define _blimp_ORTHOGRAPHIC_CAMERA

#include "camera.hpp"

namespace blimp {

    class OrthographicCamera : public blimp::Camera {
        public: 
            /** Creates an orthographic camera with the given left, right, bottom, top, near and far planes. 
             * @param left The left plane
             * @param right The right plane
             * @param bottom The bottom plane
             * @param top The top plane
             * @param near The near plane
             * @param far The far plane
            */
            OrthographicCamera(float left, float right, float bottom, float top, float near, float far);

            /** Returns the left plane of the camera.
             * @return The left plane
            */
            float getLeft();

            /** Returns the right plane of the camera.
             * @return The right plane
            */
            float getRight();

            /** Returns the bottom plane of the camera.
             * @return The bottom plane
            */
            float getBottom();

            /** Returns the top plane of the camera.
             * @return The top plane
            */
            float getTop();

            /** Returns the near plane of the camera.
             * @return The near plane
            */
            float getNear();

            /** Returns the far plane of the camera.
             * @return The far plane
            */
            float getFar();

            /** Sets the left plane of the camera.
             * @param left The new left plane
            */
            void setLeft(float left);

            /** Sets the right plane of the camera.
             * @param right The new right plane
            */
            void setRight(float right);

            /** Sets the bottom plane of the camera.
             * @param bottom The new bottom plane
            */
            void setBottom(float bottom);

            /** Sets the top plane of the camera.
             * @param top The new top plane
            */
            void setTop(float top);

            /** Sets the near plane of the camera.
             * @param near The new near plane
            */
            void setNear(float near);

            /** Sets the far plane of the camera.
             * @param far The new far plane
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
            float left;
            float right;
            float bottom;
            float top;
            float near;
            float far;
    };

}

#endif