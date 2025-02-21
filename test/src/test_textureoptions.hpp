#include <gtest/gtest.h>
#include "../../src/textureoptions.hpp"

class TextureOptionsTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            options = new blimp::TextureOptions();
            options2 = new blimp::TextureOptions(blimp::TextureOptions::WrapMode::MIRROR);
            options3 = new blimp::TextureOptions(blimp::TextureOptions::WrapMode::CLAMP_EDGE, blimp::TextureOptions::FilterMode::NEAREST);
            options4 = new blimp::TextureOptions(blimp::TextureOptions::FilterMode::NEAREST);
            options5 = new blimp::TextureOptions(
                0.5f,
                1.25f,
                blimp::TextureOptions::WrapMode::REPEAT,
                blimp::TextureOptions::WrapMode::MIRROR,
                blimp::TextureOptions::FilterMode::NEAREST,
                blimp::TextureOptions::FilterMode::LINEAR_MIPMAP_NEAREST
            );
            options6 = new blimp::TextureOptions(2.0f, 3.0f);
        }

        virtual void TearDown() {
            delete options;
            delete options2;
            delete options3;
            delete options4;
            delete options5;
            delete options6;
        }

        blimp::TextureOptions* options;
        blimp::TextureOptions* options2;
        blimp::TextureOptions* options3;
        blimp::TextureOptions* options4;
        blimp::TextureOptions* options5;
        blimp::TextureOptions* options6;
};

TEST_F(TextureOptionsTest, IsNotNull) {
    ASSERT_NE(options, nullptr);
    ASSERT_NE(options2, nullptr);
    ASSERT_NE(options3, nullptr);
    ASSERT_NE(options4, nullptr);
    ASSERT_NE(options5, nullptr);
    ASSERT_NE(options6, nullptr);
}

TEST_F(TextureOptionsTest, OptionsCorrect) {
    ASSERT_EQ(options -> getScaleS(), 1.0f);
    ASSERT_EQ(options -> getScaleT(), 1.0f);
    ASSERT_EQ(options -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options -> getWrapModeT(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options -> getMinFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options2 -> getScaleS(), 1.0f);
    ASSERT_EQ(options2 -> getScaleT(), 1.0f);
    ASSERT_EQ(options2 -> getWrapModeS(), blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options2 -> getWrapModeT(), blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options2 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options2 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options3 -> getScaleS(), 1.0f);
    ASSERT_EQ(options3 -> getScaleT(), 1.0f);
    ASSERT_EQ(options3 -> getWrapModeS(), blimp::TextureOptions::WrapMode::CLAMP_EDGE);
    ASSERT_EQ(options3 -> getWrapModeT(), blimp::TextureOptions::WrapMode::CLAMP_EDGE);
    ASSERT_EQ(options3 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options3 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options4 -> getScaleS(), 1.0f);
    ASSERT_EQ(options4 -> getScaleT(), 1.0f);
    ASSERT_EQ(options4 -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options4 -> getWrapModeT(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options4 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options4 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options5 -> getScaleS(), 0.5f);
    ASSERT_EQ(options5 -> getScaleT(), 1.25f);
    ASSERT_EQ(options5 -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options5 -> getWrapModeT(), blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options5 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options5 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR_MIPMAP_NEAREST);
    ASSERT_EQ(options6 -> getScaleS(), 2.0f);
    ASSERT_EQ(options6 -> getScaleT(), 3.0f);
    ASSERT_EQ(options6 -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options6 -> getWrapModeT(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options6 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options6 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
}

TEST_F(TextureOptionsTest, SetScale1) {
    options -> setScale(0.4f);
    ASSERT_EQ(options -> getScaleS(), 0.4f);
    ASSERT_EQ(options -> getScaleT(), 0.4f);
}

TEST_F(TextureOptionsTest, SetScale2) {
    options -> setScale(2.0f, 3.0f);
    ASSERT_EQ(options -> getScaleS(), 2.0f);
    ASSERT_EQ(options -> getScaleT(), 3.0f);
}

TEST_F(TextureOptionsTest, SetScaleS) {
    options -> setScale(1.0f);
    options -> setScaleS(10.0f);
    ASSERT_EQ(options -> getScaleS(), 10.0f);
    ASSERT_EQ(options -> getScaleT(), 1.0f);
}

TEST_F(TextureOptionsTest, SetScaleT) {
    options -> setScale(1.0f);
    options -> setScaleT(10.0f);
    ASSERT_EQ(options -> getScaleS(), 1.0f);
    ASSERT_EQ(options -> getScaleT(), 10.0f);
}

TEST_F(TextureOptionsTest, SetWrapMode1) {
    options -> setWrapMode(blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
}

TEST_F(TextureOptionsTest, SetWrapMode2) {
    options -> setWrapMode(blimp::TextureOptions::WrapMode::REPEAT, blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options -> getWrapModeT(), blimp::TextureOptions::WrapMode::MIRROR);
}

TEST_F(TextureOptionsTest, SetWrapModeS) {
    options -> setWrapMode(blimp::TextureOptions::WrapMode::REPEAT);
    options -> setWrapModeS(blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options -> getWrapModeS(), blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options -> getWrapModeT(), blimp::TextureOptions::WrapMode::REPEAT);
}

TEST_F(TextureOptionsTest, SetWrapModeT) {
    options -> setWrapMode(blimp::TextureOptions::WrapMode::REPEAT);
    options -> setWrapModeT(blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options -> getWrapModeT(), blimp::TextureOptions::WrapMode::MIRROR);
}

TEST_F(TextureOptionsTest, SetFilterMode1) {
    options -> setFilterMode(blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options -> getMinFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options -> getMagFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
}

TEST_F(TextureOptionsTest, SetFilterMode2) {
    options -> setFilterMode(blimp::TextureOptions::FilterMode::LINEAR, blimp::TextureOptions::FilterMode::LINEAR_MIPMAP_NEAREST);
    ASSERT_EQ(options -> getMinFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR_MIPMAP_NEAREST);
}

TEST_F(TextureOptionsTest, SetMinFilterMode) {
    options -> setFilterMode(blimp::TextureOptions::FilterMode::NEAREST);
    options -> setMinFilterMode(blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options -> getMinFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options -> getMagFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
}

TEST_F(TextureOptionsTest, SetMagFilterMode) {
    options -> setFilterMode(blimp::TextureOptions::FilterMode::NEAREST);
    options -> setMagFilterMode(blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options -> getMinFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
}
