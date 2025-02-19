#include <gtest/gtest.h>
#include "../../src/ambientlight.hpp"


class AmbientLightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            ambientLight = new blimp::AmbientLight();
            ambientLight2 = new blimp::AmbientLight(blimp::Color(blimp::Color::PURPLE), 0.77f);
        }

        virtual void TearDown() {
            delete ambientLight;
            delete ambientLight2;
        }

        blimp::AmbientLight *ambientLight;
        blimp::AmbientLight *ambientLight2; 
        blimp::Color* white = new blimp::Color(blimp::Color::WHITE);
        blimp::Color* purple = new blimp::Color(blimp::Color::PURPLE);
};

TEST_F(AmbientLightTest, IsNotNull) {
    ASSERT_TRUE(ambientLight != NULL);
    ASSERT_TRUE(ambientLight2 != NULL);
}

TEST_F(AmbientLightTest, IsCorrectType) {
    ASSERT_TRUE(ambientLight -> getNodeType() == blimp::Node::NODE_TYPE_AMBIENT_LIGHT);
    ASSERT_TRUE(ambientLight2 -> getNodeType() == blimp::Node::NODE_TYPE_AMBIENT_LIGHT);
}

TEST_F(AmbientLightTest, IsCorrectColor) {
    blimp::Color* c1 = ambientLight -> getColor();
    blimp::Color* c2 = ambientLight2 -> getColor();
    ASSERT_EQ(c1 -> getR(), white -> getR());
    ASSERT_EQ(c1 -> getG(), white -> getG());
    ASSERT_EQ(c1 -> getB(), white -> getB());

    ASSERT_EQ(c2 -> getR(), purple -> getR());
    ASSERT_EQ(c2 -> getG(), purple -> getG());
    ASSERT_EQ(c2 -> getB(), purple -> getB());
}

TEST_F(AmbientLightTest, IsCorrectIntensity) {
    ASSERT_EQ(ambientLight -> getIntensity(), 1.0f);
    ASSERT_EQ(ambientLight2 -> getIntensity(), 0.77f);
}
