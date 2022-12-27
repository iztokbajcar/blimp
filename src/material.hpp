#ifndef _blimp_MATERIAL
#define _blimp_MATERIAL

#include <GL/glew.h>
#include <string>
#include <vector>
#include "color.hpp"

typedef std::vector<blimp::Color> ColorVector;

namespace blimp {

    class Material {
        public:
            Material();
            Material(std::string* vertexShader, std::string* fragmentShader, ColorVector* colors);
            std::string* getVertexShader();
            std::string* getFragmentShader();
            ColorVector* getColors();
            void setColors(ColorVector* colors);

        protected:
            std::string vertexShader;
            std::string fragmentShader;
            ColorVector* colors;
            GLuint program;
    };


}

#endif