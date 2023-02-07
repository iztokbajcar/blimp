#ifndef _blimp_MATERIAL
#define _blimp_MATERIAL

#include <GL/glew.h>
#include <string>
#include <vector>

namespace blimp {

    class Material {
        public:
            Material();
            Material(std::string* vertexShader, std::string* fragmentShader);
            std::string* getVertexShader();
            std::string* getFragmentShader();
            bool usesLights();
            void setUsesLights(bool usesLights);

        protected:
            std::string vertexShader;
            std::string fragmentShader;
            GLuint program;
            bool lights = false;  // if the material uses lights
    };


}

#endif