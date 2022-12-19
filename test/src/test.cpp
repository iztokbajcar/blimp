#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include "../../src/cuboid.hpp"
#include "../../src/node.hpp"
#include "../../src/perspectivecamera.hpp"
#include "../../src/window.hpp"

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

//////////////////// PerspectiveCamera ////////////////////

class PerspectiveCameraTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            perspectiveCamera = new blimp::PerspectiveCamera(45.0f, 1.0f, 0.1f, 100.0f);
        }

        virtual void TearDown() {
            delete perspectiveCamera;
        }

        blimp::PerspectiveCamera *perspectiveCamera;
};

TEST_F(PerspectiveCameraTest, ViewMatrixIsCorrect) {
    glm::mat4* viewMatrix = perspectiveCamera -> getViewMatrix();

    ASSERT_EQ(
        *viewMatrix, 
        glm::perspective(45.0f, 1.0f, 0.1f, 100.0f)
    );
}

//////////////////// Node ////////////////////

class NodeTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            node = new blimp::Node();
        }

        virtual void TearDown() {
            delete node;
        }

        blimp::Node *node;
};

TEST_F(NodeTest, Translation) {
    node -> setTranslation(1.0f, 2.0f, 3.0f);

    ASSERT_EQ(
        node -> getTranslation(),
        glm::vec3(1.0f, 2.0f, 3.0f)
    );
}

TEST_F(NodeTest, Scale) {
    node -> setScale(7.0f, 8.0f, 9.0f);

    ASSERT_EQ(
        node -> getScale(),
        glm::vec3(7.0f, 8.0f, 9.0f)
    );
}

//////////////////////////////////////////////

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 