#ifndef _blimp_CAMERA
#define _blimp_CAMERA

#include <glm/glm.hpp>

namespace blimp {
    
    class Camera {
        public:
            Camera();
            glm::mat4* getViewMatrix();
            void setViewMatrix(glm::mat4 viewMatrix);
        protected:
            glm::mat4 viewMatrix;
    };

}

#endif