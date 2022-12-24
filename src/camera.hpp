#ifndef _blimp_CAMERA
#define _blimp_CAMERA

#include <glm/glm.hpp>

#include "node.hpp"

namespace blimp {
    
    class Camera : public blimp::Node {
        public:
            Camera();
            float getFov();
            virtual glm::mat4 getViewMatrix() = 0;
            virtual glm::mat4 getProjectionMatrix() = 0;
            void setFov(float fov);
            void setViewMatrix(glm::mat4 viewMatrix);
        protected:
            float fov;
    };

}

#endif