#ifndef _blimp_PERSPECTIVE_CAMERA
#define _blimp_PERSPECTIVE_CAMERA

#include "camera.hpp"

namespace blimp {

    class PerspectiveCamera : public blimp::Camera {
        public:
            PerspectiveCamera(float fov, float aspect, float near, float far);
            float getAspect();
            float getNear();
            float getFar();
            void setAspect(float aspect);
            void setNear(float near);
            void setFar(float far);
            glm::mat4 getViewMatrix();
            glm::mat4 getProjectionMatrix();

        private:
            float aspect;
            float near;
            float far;
    };
    
}

#endif