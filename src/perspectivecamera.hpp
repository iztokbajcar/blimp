#ifndef _blimp_PERSPECTIVECAMERA
#define _blimp_PERSPECTIVECAMERA

#include "camera.hpp"

namespace blimp {

    class PerspectiveCamera : public blimp::Camera {
        public:
            PerspectiveCamera(float fov, float aspect, float near, float far);
    };
    
}

#endif