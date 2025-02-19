#include <gtest/gtest.h>
#include "../../src/texture2d.hpp"

class Texture2DTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            texture = new blimp::Texture2D("demo/assets/textures/blimp.png");
        }

        virtual void TearDown() {
            delete texture;
        }

        blimp::Texture2D *texture;
};

TEST_F(Texture2DTest, IsNotNull) {
    ASSERT_NE(texture, nullptr);
}

TEST_F(Texture2DTest, WidthCorrect) {
    ASSERT_EQ(texture -> getWidth(), 512);
}

TEST_F(Texture2DTest, HeightCorrect) {
    ASSERT_EQ(texture -> getHeight(), 512);
}

TEST_F(Texture2DTest, DataNotNull) {
    ASSERT_NE(texture -> getData(), nullptr);
}
