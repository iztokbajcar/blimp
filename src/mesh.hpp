#ifndef _blimp_MESH
#define _blimp_MESH

#include "geometry.hpp"
#include "material.hpp"
#include "node.hpp"
#include "texturable.hpp"

/** @file mesh.hpp */

namespace blimp {

    //! Represents a visible 3D object (has a geometry and a material)
    class Mesh : public blimp::Node, public blimp::Texturable {
        public:
            /** The default constructor. 
             * Creates a mesh with no geometry and no material. The user is encouraged to set these
             * properties before rendering the mesh.
            */
            Mesh();

            /** Construct a mesh from existing geometry and material.
             * @param geometry The geometry of the new mesh
             * @param material The material of the new mesh
             */
            Mesh(Geometry* geometry, Material* material);

            /** The default destructor. */
            ~Mesh();

            /** Returns the geometry used by this mesh. 
             * @return The geometry used by this mesh
            */
            Geometry* getGeometry();

            /** Returns the material used by this mesh.
             * @return The material used by this mesh
            */
            Material* getMaterial();

            /** Sets the geometry to be used by this mesh.
             * @param geometry The new geometry
             */
            void setGeometry(Geometry* geometry);

            /** Sets the material to be used by this mesh.
             * @param material The new material
             */
            void setMaterial(Material* material);

        protected:
            Geometry* geometry = nullptr;  /**< The mesh's geometry. **/
            Material* material = nullptr;  /**< The mesh's material. **/
            Texture* texture = nullptr;  /**< The mesh's texture. **/
            TextureOptions* texOptions = nullptr;  /**< The mesh's texture options. **/

        private:
            bool usingDefaultTexOptions;
    };

}

#endif