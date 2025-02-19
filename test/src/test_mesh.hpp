#include <gtest/gtest.h>
#include "../../src/mesh.hpp"

class MeshTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            mesh = new blimp::Mesh();
            mesh2 = new blimp::Mesh();
            geometry = new blimp::Geometry();
            material = new blimp::Material();
            mesh2 -> setGeometry(geometry);
            mesh2 -> setMaterial(material);
            mesh3 = new blimp::Mesh(geometry, material);
        }

        virtual void TearDown() {
            delete mesh;
            delete mesh2;
            delete mesh3;
        }

        blimp::Mesh *mesh;
        blimp::Mesh *mesh2;
        blimp::Mesh *mesh3;
        blimp::Geometry* geometry;
        blimp::Material* material;
};

TEST_F(MeshTest, IsNotNull) {
    ASSERT_TRUE(mesh != NULL);
    ASSERT_TRUE(mesh2 != NULL);
    ASSERT_TRUE(mesh3 != NULL);
}

TEST_F(MeshTest, IsCorrectGeometry) {
    ASSERT_TRUE(mesh -> getGeometry() == NULL);
    ASSERT_TRUE(mesh2 -> getGeometry() == geometry);
    ASSERT_TRUE(mesh3 -> getGeometry() == geometry);
}

TEST_F(MeshTest, IsCorrectMaterial) {
    ASSERT_TRUE(mesh -> getMaterial() == NULL);
    ASSERT_TRUE(mesh2 -> getMaterial() == material);
    ASSERT_TRUE(mesh3 -> getMaterial() == material);
}
