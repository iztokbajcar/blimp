#ifndef _blimp_MESH
#define _blimp_MESH

#include "geometry.hpp"
#include "material.hpp"
#include "node.hpp"

namespace blimp {

    class Mesh : public blimp::Node {
        public:
            Mesh();
            Mesh(Geometry* geometry, Material* material);
            ~Mesh();

            Geometry* getGeometry();
            Material* getMaterial();

        private:
            Geometry* geometry = nullptr;
            Material* material = nullptr;
    };

}

#endif