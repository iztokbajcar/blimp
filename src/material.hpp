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

        protected:
            std::string vertexShader;
            std::string fragmentShader;
            GLuint program;
    };


}

#endif