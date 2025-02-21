#include <gtest/gtest.h>
#include "../../src/texturable.hpp"
#include "../../src/texture2d.hpp"

class TexturableTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            texture = new blimp::Texture2D("demo/assets/textures/blimp.png");
            options = new blimp::TextureOptions();
            texturable = new blimp::Texturable();
        }
        virtual void TearDown() {
            delete texturable;
            delete texture;
            delete options;
        }

        blimp::Texturable *texturable;
        blimp::Texture2D *texture;
        blimp::TextureOptions *options;
};

TEST_F(TexturableTest, IsNotNull) {
    ASSERT_NE(texturable, nullptr);
}

TEST_F(TexturableTest, SetTexture) {
    ASSERT_EQ(texturable -> getTexture(), nullptr);
    texturable -> setTexture(texture);
    ASSERT_EQ(texturable -> getTexture(), texture);
}

TEST_F(TexturableTest, SetTextureOptions) {
    ASSERT_NE(texturable -> getTextureOptions(), nullptr);
    ASSERT_NE(texturable -> getTextureOptions(), options);
    texturable -> setTextureOptions(options);
    ASSERT_EQ(texturable -> getTextureOptions(), options);
}

TEST_F(TexturableTest, SetTextureWithTextureOptions) {
    texturable -> setTexture(texture, options);
    ASSERT_EQ(texturable -> getTexture(), texture);
    ASSERT_EQ(texturable -> getTextureOptions(), options);
}


