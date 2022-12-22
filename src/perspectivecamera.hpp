#ifndef _blimp_PERSPECTIVE_CAMERA
#define _blimp_PERSPECTIVE_CAMERA

#include "camera.hpp"

namespace blimp {

    class PerspectiveCamera : public blimp::Camera {
        public:
            PerspectiveCamera(float fov, float aspect, float near, float far);
            float getFov();
            float getNear();
            float getFar();
            glm::mat4 getViewMatrix();
            glm::mat4 getProjectionMatrix();

        private:
            float fov;
            float aspect;
            float near;
            float far;
    };
    
}

#endif