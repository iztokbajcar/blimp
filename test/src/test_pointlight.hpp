#include <gtest/gtest.h>
#include "../../src/pointlight.hpp"

class PointLightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            pointLight = new blimp::PointLight();
            pointLight2 = new blimp::PointLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f);
        }

        virtual void TearDown() {
            delete pointLight;
            delete pointLight2;
        }

        blimp::PointLight *pointLight;
        blimp::PointLight *pointLight2;
};

TEST_F(PointLightTest, IsNotNull) {
    ASSERT_NE(pointLight, nullptr);
    ASSERT_NE(pointLight2, nullptr);
}

TEST_F(PointLightTest, TypeIsCorrect) {
    ASSERT_EQ(
        pointLight -> getNodeType(),
        blimp::Node::NODE_TYPE_POINT_LIGHT
    );

    ASSERT_EQ(
        pointLight2 -> getNodeType(),
        blimp::Light::NODE_TYPE_POINT_LIGHT
    );
}

TEST_F(PointLightTest, ColorIsCorrect) {
    blimp::Color* c1 = pointLight -> getColor();
    blimp::Color* c2 = pointLight2 -> getColor();

    ASSERT_EQ(c1 -> getR(), 1.0f);
    ASSERT_EQ(c1 -> getG(), 1.0f);
    ASSERT_EQ(c1 -> getB(), 1.0f);

    ASSERT_EQ(c2 -> getR(), 0.0f);
    ASSERT_EQ(c2 -> getG(), 1.0f);
    ASSERT_EQ(c2 -> getB(), 1.0f);
}

TEST_F(PointLightTest, IntensityIsCorrect) {
    ASSERT_EQ(
        pointLight -> getIntensity(),
        1.0f
    );

    ASSERT_EQ(
        pointLight2 -> getIntensity(),
        0.6f
    );
}

TEST_F(PointLightTest, AttenuationIsCorrect) {
    ASSERT_EQ(
        pointLight -> getAttenuation(),
        1.0f
    );

    ASSERT_EQ(
        pointLight2 -> getAttenuation(),
        0.5f
    );
}

TEST_F(PointLightTest, SetAttenuation) {
    blimp::PointLight* pointLightAttenuationTest = new blimp::PointLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f);
    pointLightAttenuationTest -> setAttenuation(0.2f);

    ASSERT_EQ(
        pointLightAttenuationTest -> getAttenuation(),
        0.2f
    );
}
