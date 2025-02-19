#include <gtest/gtest.h>
#include "../../src/directionallight.hpp"

class DirectionalLightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            directionalLight = new blimp::DirectionalLight();
            directionalLight2 = new blimp::DirectionalLight(blimp::Color(blimp::Color::PURPLE), 0.5f);
        }

        virtual void TearDown() {
            delete directionalLight;
            delete directionalLight2;
        }

        blimp::DirectionalLight *directionalLight;
        blimp::DirectionalLight *directionalLight2; 
        blimp::Color* white = new blimp::Color(blimp::Color::WHITE);
        blimp::Color* purple = new blimp::Color(blimp::Color::PURPLE);
};

TEST_F(DirectionalLightTest, IsNotNull) {
    ASSERT_TRUE(directionalLight != NULL);
    ASSERT_TRUE(directionalLight2 != NULL);
}

TEST_F(DirectionalLightTest, IsCorrectType) {
    ASSERT_TRUE(directionalLight -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
    ASSERT_TRUE(directionalLight2 -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
}

TEST_F(DirectionalLightTest, IsCorrectColor) {
    blimp::Color* c1 = directionalLight -> getColor();
    blimp::Color* c2 = directionalLight2 -> getColor();
    ASSERT_EQ(c1 -> getR(), white -> getR());
    ASSERT_EQ(c1 -> getG(), white -> getG());
    ASSERT_EQ(c1 -> getB(), white -> getB());

    ASSERT_EQ(c2 -> getR(), purple -> getR());
    ASSERT_EQ(c2 -> getG(), purple -> getG());
    ASSERT_EQ(c2 -> getB(), purple -> getB());
}

TEST_F(DirectionalLightTest, IsCorrectIntensity) {
    ASSERT_EQ(directionalLight -> getIntensity(), 1.0f);
    ASSERT_EQ(directionalLight2 -> getIntensity(), 0.5f);
}