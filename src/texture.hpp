#ifndef _blimp_TEXTURE
#define _blimp_TEXTURE

#include <SOIL/SOIL.h>
#include <string>

/** @file image.hpp */

namespace blimp {

    class Texture {
        public:
            Texture(std::string filename);
            int getWidth();
            int getHeight();
            unsigned char* getData();

        private:
            int width;
            int height;
            unsigned char* data;
    };

}

#endif