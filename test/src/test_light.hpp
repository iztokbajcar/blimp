#include <gtest/gtest.h>
#include "../../src/light.hpp"

class LightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            light = new blimp::Light();
            light2 = new blimp::Light(blimp::Color(blimp::Color::PURPLE), 0.5f);
            light3 = new blimp::Light();
            light3 -> setColor(blimp::Color(blimp::Color::GREEN));
            light3 -> setIntensity(0.2f);
        }

        virtual void TearDown() {
            delete light;
            delete light2;
            delete light3;
        }

        blimp::Light *light;
        blimp::Light *light2; 
        blimp::Light *light3;
        blimp::Color* white = new blimp::Color(blimp::Color::WHITE);
        blimp::Color* purple = new blimp::Color(blimp::Color::PURPLE);
};

TEST_F(LightTest, IsNotNull) {
    ASSERT_TRUE(light != NULL);
    ASSERT_TRUE(light2 != NULL);
    ASSERT_TRUE(light3 != NULL);
}

TEST_F(LightTest, IsCorrectType) {
    ASSERT_TRUE(light -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
    ASSERT_TRUE(light2 -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
    ASSERT_TRUE(light3 -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
}

TEST_F(LightTest, IsCorrectColor) {
    blimp::Color* c1 = light -> getColor();
    blimp::Color* c2 = light2 -> getColor();
    blimp::Color* c3 = light3 -> getColor();

    ASSERT_EQ(c1 -> getR(), white -> getR());
    ASSERT_EQ(c1 -> getG(), white -> getG());
    ASSERT_EQ(c1 -> getB(), white -> getB());

    ASSERT_EQ(c2 -> getR(), purple -> getR());
    ASSERT_EQ(c2 -> getG(), purple -> getG());
    ASSERT_EQ(c2 -> getB(), purple -> getB());

    ASSERT_EQ(c3 -> getR(), 0.0f);
    ASSERT_EQ(c3 -> getG(), 0.5f);
    ASSERT_EQ(c3 -> getB(), 0.0f);
}

TEST_F(LightTest, IsCorrectIntensity) {
    ASSERT_EQ(light -> getIntensity(), 1.0f);
    ASSERT_EQ(light2 -> getIntensity(), 0.5f);
    ASSERT_EQ(light3 -> getIntensity(), 0.2f);
}