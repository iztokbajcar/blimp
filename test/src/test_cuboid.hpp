#include <gtest/gtest.h>
#include "../../src/cuboid.hpp"

class CuboidTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            cuboid = new blimp::Cuboid(1, 2, 3);
        }

        virtual void TearDown() {
            delete cuboid;
        }

        blimp::Cuboid *cuboid;
};

TEST_F(CuboidTest, IsCenteredAtOrigin) {
    GLfloat* verts = cuboid -> getVertices();
    int vertCount = cuboid -> getVertexCount();

    GLfloat sum = 0.0f;

    for (int i = 0; i < vertCount; i++) {
        sum += verts[i];
    }

    ASSERT_EQ(sum, 0);
}