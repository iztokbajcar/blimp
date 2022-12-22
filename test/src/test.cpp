#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include "../../src/cuboid.hpp"
#include "../../src/material.hpp"
#include "../../src/node.hpp"
#include "../../src/perspectivecamera.hpp"
#include "../../src/window.hpp"

//////////////////// Window ////////////////////

class WindowTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            // window = new blimp::Window("BlimpTest");
            scene = new blimp::Node(NULL, NULL);
            camera = new blimp::PerspectiveCamera(60.0f, 800.0f/600.0f, 0.1f, 100.0f);

            this -> window = new blimp::Window("BlimpTest", 800, 600);
            this -> window -> setScene(scene);
            this -> window -> setCamera(camera);
        }

        virtual void TearDown() {
            delete window;
            delete scene;
            delete camera;
        }

        blimp::Window *window;
        blimp::Node *scene;
        blimp::PerspectiveCamera *camera;
};

TEST_F(WindowTest, IsNotNull) {
    ASSERT_NE(window, nullptr);
    blimp::Node* cube = new blimp::Node(new blimp::Cuboid(1, 1, 1), new blimp::Material());
    cube -> setTranslation(0, 0, 5);
    scene -> addChild(cube);
    window -> setScene(scene);
    window -> setCamera(camera);
    window -> run();
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
    glm::mat4 viewMatrix = perspectiveCamera -> getViewMatrix();

    ASSERT_EQ(
        viewMatrix, 
        glm::inverse(glm::perspective(45.0f, 1.0f, 0.1f, 100.0f))
    );
}

//////////////////// Node ////////////////////

class NodeTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            node = new blimp::Node(new blimp::Geometry(), new blimp::Material());
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

TEST_F(NodeTest, Rotation) {
    node -> setRotation(4.0f, 5.0f, 6.0f);

    ASSERT_EQ(
        node -> getRotation(),
        glm::quat(glm::vec3(4.0f, 5.0f, 6.0f))
    );
}

TEST_F(NodeTest, Scale) {
    node -> setScale(7.0f, 8.0f, 9.0f);

    ASSERT_EQ(
        node -> getScale(),
        glm::vec3(7.0f, 8.0f, 9.0f)
    );
}

TEST_F(NodeTest, TransformationMatrix) {
    glm::mat4 testMatrix = glm::mat4(1.0f);
    // scale
    testMatrix[0][0] = 2.0f;  // [col][row]
    testMatrix[1][1] = 2.0f;
    testMatrix[2][2] = 2.0f;
    // translate
    testMatrix[3][0] = 1.0f;
    testMatrix[3][1] = 2.0f;
    testMatrix[3][2] = 3.0f;

    node -> setTranslation(1.0f, 2.0f, 3.0f);
    node -> setScale(2.0f, 2.0f, 2.0f);

    ASSERT_EQ(
        node -> getTransformationMatrix(),
        testMatrix
    );
}

TEST_F(NodeTest, Children) {
    ASSERT_EQ(
        node -> getChildren() -> size(),
        0
    );

    blimp::Node* child1 = new blimp::Node(new blimp::Geometry(), new blimp::Material());
    blimp::Node* child2 = new blimp::Node(new blimp::Geometry(), new blimp::Material());
    blimp::Node* grandchild = new blimp::Node(new blimp::Geometry(), new blimp::Material());
    node -> addChild(child1);
    node -> addChild(child2);
    child1 -> addChild(grandchild);

    ASSERT_EQ(
        node -> getChildren() -> size(),
        2
    );

    ASSERT_EQ(
        child1 -> getChildren() -> size(),
        1
    );

    ASSERT_EQ(
        child2 -> getChildren() -> size(),
        0
    );

    node -> removeChild(child1);

    ASSERT_EQ(
        child1 -> getChildren() -> size(),
        1
    );

    ASSERT_EQ(
        node -> getChildren() -> size(),
        1
    );

    delete child1;
    delete child2;
}

//////////////////////////////////////////////

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 