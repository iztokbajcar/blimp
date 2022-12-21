#ifndef _blimp_MATERIAL
#define _blimp_MATERIAL

namespace blimp {

    class Material {
        public:
            Material();
            Material(char* vertexShader, char* fragmentShader);

        private:
            char* vertexShader;
            char* fragmentShader;
    };


}

#endif