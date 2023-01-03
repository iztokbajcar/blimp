#ifndef _blimp_GEOMETRY
#define _blimp_GEOMETRY

#include <vector>
#include <GL/glew.h>

#include "color.hpp"

typedef std::vector<blimp::Color> ColorVector;

namespace blimp {

    class Geometry {
        public:
            Geometry();
            Geometry(ColorVector* colors);
            GLfloat* getVertices();
            virtual GLfloat* getColors();
            GLfloat* getNormals();
            int getVertexCount();
            virtual void setColors(ColorVector* colors);
        protected:
            GLfloat* vertices = nullptr;
            GLfloat* colors = nullptr;
            GLfloat* normals = nullptr;
            int vertexCount = 0;
    };

}

#endif