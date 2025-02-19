#include <gtest/gtest.h>
#include "../../src/color.hpp"

class ColorTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            color = new blimp::Color();
            color2 = new blimp::Color(blimp::Color::PURPLE);
            color3 = new blimp::Color(0.1f, 0.2f, 0.3f);
            color4 = new blimp::Color(0.1f, 0.2f, 0.3f, 0.4f);
        }

        virtual void TearDown() {
            delete color;
            delete color2;
            delete color3;
            delete color4;
        }

        blimp::Color *color;
        blimp::Color *color2;
        blimp::Color *color3;
        blimp::Color *color4;
};

TEST_F(ColorTest, IsNotNull) {
    ASSERT_TRUE(color != NULL);
    ASSERT_TRUE(color2 != NULL);
    ASSERT_TRUE(color3 != NULL);
    ASSERT_TRUE(color4 != NULL);
}

TEST_F(ColorTest, IsCorrect) {
    ASSERT_EQ(color -> getR(), 0.0f);
    ASSERT_EQ(color -> getG(), 0.0f);
    ASSERT_EQ(color -> getB(), 0.0f);
    ASSERT_EQ(color -> getA(), 1.0f);

    ASSERT_EQ(color2 -> getR(), 0.5f);
    ASSERT_EQ(color2 -> getG(), 0.0f);
    ASSERT_EQ(color2 -> getB(), 0.5f);
    ASSERT_EQ(color2 -> getA(), 1.0f);

    ASSERT_EQ(color3 -> getR(), 0.1f);
    ASSERT_EQ(color3 -> getG(), 0.2f);
    ASSERT_EQ(color3 -> getB(), 0.3f);
    ASSERT_EQ(color3 -> getA(), 1.0f);

    ASSERT_EQ(color4 -> getR(), 0.1f);
    ASSERT_EQ(color4 -> getG(), 0.2f);
    ASSERT_EQ(color4 -> getB(), 0.3f);
    ASSERT_EQ(color4 -> getA(), 0.4f);
}
