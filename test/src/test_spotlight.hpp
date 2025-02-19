#include <gtest/gtest.h>
#include "../../src/spotlight.hpp"

class SpotLightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            spotLight = new blimp::SpotLight();
            spotLight2 = new blimp::SpotLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f, 0.2f);
        }

        virtual void TearDown() {
            delete spotLight;
            delete spotLight2;
        }

        blimp::SpotLight *spotLight;
        blimp::SpotLight *spotLight2;
};

TEST_F(SpotLightTest, IsNotNull) {
    ASSERT_NE(spotLight, nullptr);
    ASSERT_NE(spotLight2, nullptr);
}

TEST_F(SpotLightTest, TypeIsCorrect) {
    ASSERT_EQ(
        spotLight -> getNodeType(),
        blimp::Node::NODE_TYPE_SPOT_LIGHT
    );

    ASSERT_EQ(
        spotLight2 -> getNodeType(),
        blimp::Node::NODE_TYPE_SPOT_LIGHT
    );
}

TEST_F(SpotLightTest, ColorIsCorrect) {
    blimp::Color* c1 = spotLight -> getColor();
    blimp::Color* c2 = spotLight2 -> getColor();

    ASSERT_EQ(c1 -> getR(), 1.0f);
    ASSERT_EQ(c1 -> getG(), 1.0f);
    ASSERT_EQ(c1 -> getB(), 1.0f);

    ASSERT_EQ(c2 -> getR(), 0.0f);
    ASSERT_EQ(c2 -> getG(), 1.0f);
    ASSERT_EQ(c2 -> getB(), 1.0f);
}

TEST_F(SpotLightTest, IntensityIsCorrect) {
    ASSERT_EQ(
        spotLight -> getIntensity(),
        1.0f
    );

    ASSERT_EQ(
        spotLight2 -> getIntensity(),
        0.6f
    );
}

TEST_F(SpotLightTest, SetInnerCutoff) {
    blimp::SpotLight* spotLightInnerCutoffTest = new blimp::SpotLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f, 0.2f);
    spotLightInnerCutoffTest -> setInnerCutoff(0.4f);

    ASSERT_EQ(
        spotLightInnerCutoffTest -> getInnerCutoff(),
        0.4f
    );
}

TEST_F(SpotLightTest, SetOuterCutoff) {
    blimp::SpotLight* spotLightOuterCutoffTest = new blimp::SpotLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f, 0.2f);
    spotLightOuterCutoffTest -> setOuterCutoff(0.3f);

    ASSERT_EQ(
        spotLightOuterCutoffTest -> getOuterCutoff(),
        0.3f
    );
}
