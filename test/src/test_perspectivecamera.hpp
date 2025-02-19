#include <gtest/gtest.h>
#include "../../src/perspectivecamera.hpp"

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
        glm::inverse(glm::mat4(1.0f))
    );
}

TEST_F(PerspectiveCameraTest, ParametersAreCorrect) {
    ASSERT_EQ(
        perspectiveCamera -> getFov(),
        45.0f
    );

    ASSERT_EQ(
        perspectiveCamera -> getAspect(),
        1.0f
    );

    ASSERT_EQ(
        perspectiveCamera -> getNear(),
        0.1f
    );

    ASSERT_EQ(
        perspectiveCamera -> getFar(),
        100.0f
    );
}

TEST_F(PerspectiveCameraTest, SetParameters) {
    perspectiveCamera -> setFov(90.0f);
    perspectiveCamera -> setAspect(2.0f);
    perspectiveCamera -> setNear(0.2f);
    perspectiveCamera -> setFar(200.0f);

    ASSERT_EQ(
        perspectiveCamera -> getFov(),
        90.0f
    );

    ASSERT_EQ(
        perspectiveCamera -> getAspect(),
        2.0f
    );

    ASSERT_EQ(
        perspectiveCamera -> getNear(),
        0.2f
    );

    ASSERT_EQ(
        perspectiveCamera -> getFar(),
        200.0f
    );
}
