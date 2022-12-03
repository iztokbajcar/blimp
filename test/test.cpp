#include <glm/glm.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include "../src/cuboid.hpp"
#include "../src/window.hpp"

//////////////////// Window ////////////////////

class WindowTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            window = new blimp::Window("BlimpTest");
        }

        virtual void TearDown() {
            delete window;
        }

        blimp::Window *window;
};

TEST_F(WindowTest, IsNotNull) {
    ASSERT_NE(window, nullptr);
}

TEST_F(WindowTest, IsNotNullAfterOpen) {
    ASSERT_NE(window, nullptr);
} 

//////////////////// Cuboid ////////////////////

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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 
