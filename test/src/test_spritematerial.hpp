#include <gtest/gtest.h>
#include "../../src/spritematerial.hpp"

class SpriteMaterialTest : public testing::Test {
    protected:
        virtual void SetUp() {
            material = new blimp::SpriteMaterial();
        }

        virtual void TearDown() {
            delete material;
        }

        blimp::SpriteMaterial *material;
};

TEST_F(SpriteMaterialTest, IsNotNull) {
    ASSERT_NE(material, nullptr);
}

TEST_F(SpriteMaterialTest, VertexShaderSourceNotEmpty) {
    ASSERT_NE(material -> getVertexShader() -> generateSource() -> length(), 0);
}

TEST_F(SpriteMaterialTest, FragmentShaderSourceNotEmpty) {
    ASSERT_NE(material -> getFragmentShader() -> generateSource() -> length(), 0);
}