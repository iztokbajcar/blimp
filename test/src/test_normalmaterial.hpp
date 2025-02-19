#include <gtest/gtest.h>
#include "../../src/normalmaterial.hpp"

class NormalMaterialTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            normalMaterial = new blimp::NormalMaterial();
        }

        virtual void TearDown() {
            delete normalMaterial;
        }

        blimp::NormalMaterial *normalMaterial;
};

TEST_F(NormalMaterialTest, IsNotNull) {
    ASSERT_TRUE(normalMaterial != NULL);
}

TEST_F(NormalMaterialTest, NormalMaterialVertexShaderNotEmpty) {
    ASSERT_TRUE(normalMaterial -> getVertexShader() != NULL);
    ASSERT_NE(normalMaterial -> getVertexShader() -> generateSource() -> length(), 0);
}

TEST_F(NormalMaterialTest, NormalMaterialFragmentShaderNotEmpty) {
    ASSERT_TRUE(normalMaterial -> getFragmentShader() != NULL);
    ASSERT_NE(normalMaterial -> getFragmentShader() -> generateSource() -> length(), 0);
}