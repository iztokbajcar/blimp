#include <gtest/gtest.h>
#include "../../src/orthographiccamera.hpp"

class OrthographicCameraTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            orthographicCamera = new blimp::OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
        }

        virtual void TearDown() {
            delete orthographicCamera;
        }

        blimp::OrthographicCamera *orthographicCamera;
};

TEST_F(OrthographicCameraTest, ViewMatrixIsCorrect) {
    glm::mat4 viewMatrix = orthographicCamera -> getViewMatrix();

    ASSERT_EQ(
        viewMatrix, 
        glm::inverse(glm::mat4(1.0f))
    );
}

TEST_F(OrthographicCameraTest, ParametersAreCorrect) {
    ASSERT_EQ(
        orthographicCamera -> getLeft(),
        -1.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getRight(),
        1.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getBottom(),
        -1.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getTop(),
        1.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getNear(),
        0.1f
    );

    ASSERT_EQ(
        orthographicCamera -> getFar(),
        100.0f
    );
}

TEST_F(OrthographicCameraTest, SetParameters) {
    orthographicCamera -> setLeft(-2.0f);
    orthographicCamera -> setRight(2.0f);
    orthographicCamera -> setBottom(-2.0f);
    orthographicCamera -> setTop(2.0f);
    orthographicCamera -> setNear(0.2f);
    orthographicCamera -> setFar(200.0f);

    ASSERT_EQ(
        orthographicCamera -> getLeft(),
        -2.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getRight(),
        2.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getBottom(),
        -2.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getTop(),
        2.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getNear(),
        0.2f
    );

    ASSERT_EQ(
        orthographicCamera -> getFar(),
        200.0f
    );
}

TEST_F(OrthographicCameraTest, ProjectionMatrixIsCorrect) {
    orthographicCamera = new blimp::OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    glm::mat4 projectionMatrix = orthographicCamera -> getProjectionMatrix();

    ASSERT_EQ(
        projectionMatrix,
        glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f)
    );
}
