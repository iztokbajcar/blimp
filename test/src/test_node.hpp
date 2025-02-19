#include <gtest/gtest.h>
#include <glm/gtx/string_cast.hpp>
#include "../../src/node.hpp"

class NodeTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            node = new blimp::Node();
            node2 = new blimp::Node();
            node -> addChild(node2);
        }

        virtual void TearDown() {
            delete node;
            delete node2;
        }

        blimp::Node *node;
        blimp::Node *node2;
};

TEST_F(NodeTest, Translation) {
    node -> setTranslation(1.0f, 2.0f, 3.0f);

    ASSERT_EQ(
        node -> getTranslation(),
        glm::vec3(1.0f, 2.0f, 3.0f)
    );

    ASSERT_EQ(
        node2 -> getTranslation(),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    node -> translate(-1.0f, -2.0f, -3.0f);

    ASSERT_EQ(
        node -> getTranslation(),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    ASSERT_EQ(
        node2 -> getTranslation(),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    node2 -> setTranslation(1.0f, 2.0f, 3.0f);

    ASSERT_EQ(
        node -> getTranslation(),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    ASSERT_EQ(
        node2 -> getTranslation(),
        glm::vec3(1.0f, 2.0f, 3.0f)
    );

    node2 -> translate(-1.0f, -2.0f, -3.0f);

    ASSERT_EQ(
        node -> getTranslation(),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    ASSERT_EQ(
        node2 -> getTranslation(),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
}

TEST_F(NodeTest, Rotation) {   
    node -> setRotation(4.0f, 5.0f, 6.0f);

    ASSERT_EQ(
        glm::to_string(node -> getRotation()),
        "quat(-0.406853, {-0.686041, -0.349363, 0.491695})"
    );

    node -> setRotation(0.0f, 0.0f, 0.0f);
    node -> rotate(1.0f, 2.0f, 3.0f);

    ASSERT_EQ(
        glm::to_string(node -> getRotation()),
        "quat(-0.368871, {-0.754934, 0.206149, -0.501509})"
    );
}

TEST_F(NodeTest, Scale) {
    node -> setScale(7.0f, 8.0f, 9.0f);

    ASSERT_EQ(
        node -> getScale(),
        glm::vec3(7.0f, 8.0f, 9.0f)
    );
}

TEST_F(NodeTest, ForwardDirection) {
    node -> setRotation(0.0f, 0.0f, 0.0f);

    ASSERT_EQ(
        node -> getForwardDirection(),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    node -> setRotation(0.0f, glm::half_pi<float>(), 0.0f);

    ASSERT_LT(
        node -> getForwardDirection().z - glm::vec3(1.0f, 0.0f, 0.0f).z,
        1e-7f
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

TEST_F(NodeTest, GlobalTransformationMatrix) {
    node -> setTranslation(1.0f, 2.0f, 3.0f);
    node2 -> setTranslation(3.0f, 2.0f, 1.0f);

    glm::mat4 testMatrix = glm::mat4(1.0f);
    // translate
    testMatrix[3][0] = 1.0f;
    testMatrix[3][1] = 2.0f;
    testMatrix[3][2] = 3.0f;

    glm::mat4 testMatrix2 = glm::mat4(1.0f);
    // translate
    testMatrix2[3][0] = 4.0f;
    testMatrix2[3][1] = 4.0f;
    testMatrix2[3][2] = 4.0f;

    ASSERT_EQ(
        node -> getGlobalTransformationMatrix(),
        testMatrix
    );
    
    ASSERT_EQ(
        node2 -> getGlobalTransformationMatrix(),
        testMatrix2
    );
}

TEST_F(NodeTest, ParentTransformationMatrix) {
    node -> setTranslation(1.0f, 2.0f, 3.0f);
    node2 -> setTranslation(3.0f, 2.0f, 1.0f);

    glm::mat4 testMatrix = glm::mat4(1.0f);
    // translate
    testMatrix[3][0] = 1.0f;
    testMatrix[3][1] = 2.0f;
    testMatrix[3][2] = 3.0f;

    ASSERT_EQ(
        node -> getParentTransformationMatrix(),
        glm::mat4(1.0f)
    );

    ASSERT_EQ(
        node2 -> getParentTransformationMatrix(),
        testMatrix
    );
}



TEST_F(NodeTest, Children) {
    ASSERT_EQ(
        node2 -> getChildren() -> size(),
        0
    );

    blimp::Node* child1 = new blimp::Node();
    blimp::Node* child2 = new blimp::Node();
    blimp::Node* grandchild = new blimp::Node();
    node2 -> addChild(child1);
    node2 -> addChild(child2);
    child1 -> addChild(grandchild);

    ASSERT_EQ(
        node2 -> getChildren() -> size(),
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

    node2 -> removeChild(child1);

    ASSERT_EQ(
        child1 -> getChildren() -> size(),
        1
    );

    ASSERT_EQ(
        node2 -> getChildren() -> size(),
        1
    );

    std::vector<blimp::Node*> vec = node2 -> traverseChildren();
    
    ASSERT_EQ(
        vec.size(),
        1
    );

    delete child1;
    delete child2;
}

TEST_F(NodeTest, Parent) {
    ASSERT_EQ(
        node -> getParent(),
        nullptr
    );

    ASSERT_EQ(
        node2 -> getParent(),
        node
    );
}