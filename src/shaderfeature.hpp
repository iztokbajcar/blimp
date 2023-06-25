#ifndef _blimp_SHADER_FEATURE
#define _blimp_SHADER_FEATURE

/** @file shaderfeature.hpp */

namespace blimp {

    //! An enum representing the features that a shader can use.
    enum ShaderFeature {
        USES_POSITION,
        USES_CAMERA_POSITION,
        USES_COLOR,
        USES_LIGHTS,
        USES_NORMALS,
        USES_TEXTURES
    };

}

#endif