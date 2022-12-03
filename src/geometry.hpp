#ifndef _blimp_GEOMETRY
#define _blimp_GEOMETRY

#include <vector>
#include <GL/glew.h>

namespace blimp {

    class Geometry {
        public:
            Geometry();
            GLfloat* getVertices();
            int getVertexCount();
        protected:
            GLfloat* vertices = nullptr;
            GLfloat* normals = nullptr;
            int vertexCount = 0;
    };

}

#endif