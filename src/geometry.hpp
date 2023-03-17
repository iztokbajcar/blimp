#ifndef _blimp_GEOMETRY
#define _blimp_GEOMETRY

#include <vector>
#include <GL/glew.h>

#include "color.hpp"

/** @file geometry.hpp */

/** A vector of Color objects. */
typedef std::vector<blimp::Color> ColorVector;

namespace blimp {

    //! Represents a 3D shape (i.e. defines its vertices with their respective attributes).
    class Geometry {
        public:
            /** The default constructor. 
             * Creates an empty geometry.
            */
            Geometry();

            /** Creates a geometry with the given colors.
             * @param colors The colors of the geometry's vertices
             */           
            Geometry(ColorVector* colors);

            /** Returns the geometry's vertices.
             * @return The geometry's vertices
            */
            GLfloat* getVertices();

            /** Returns the geometry's colors.
             * @return The geometry's colors
            */
            virtual GLfloat* getColors();

            /** Returns the geometry's normals.
             * @return The geometry's normals
            */
            GLfloat* getNormals();

            /** Returns the geometry's texture coordinates.
             * @return The texture coordinates
            */
            GLfloat* getTexCoords();

            /** Returns the number of vertices in the geometry.
             * @return The number of vertices in the geometry
            */
            int getVertexCount();

            /** Sets the geometry's colors.
             * @param colors The colors of the geometry's vertices
            */
            virtual void setColors(ColorVector* colors);
        protected:
            GLfloat* vertices = nullptr;  /**< The geometry's vertices. */  // no indexes because we need to use normals and define each triangle's vertex separately
            GLfloat* colors = nullptr;  /**< The geometry's colors. */
            GLfloat* normals = nullptr;  /**< The geometry's normals. */
            GLfloat* texCoords = nullptr;  /**< The geometry's texture coordinates. */
            
            int vertexCount = 0;  /**< The number of vertices in the geometry. Should not be set manually. */
    };

}

#endif