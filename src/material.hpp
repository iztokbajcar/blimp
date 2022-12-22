#ifndef _blimp_MATERIAL
#define _blimp_MATERIAL

#include <GL/glew.h>
#include <string>

namespace blimp {

    class Material {
        public:
            Material();
            Material(std::string* vertexShader, std::string* fragmentShader);
            std::string* getVertexShader();
            std::string* getFragmentShader();

        private:
            std::string vertexShader;
            std::string fragmentShader;
            GLuint program;
    };


}

#endif