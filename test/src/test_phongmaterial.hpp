#include <gtest/gtest.h>
#include "../../src/phongmaterial.hpp"

class PhongMaterialTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            phongMaterial = new blimp::PhongMaterial();
            phongMaterial2 = new blimp::PhongMaterial(10.0f, 0.5f);
        }

        virtual void TearDown() {
            delete phongMaterial;
            delete phongMaterial2;
        }

        blimp::PhongMaterial *phongMaterial;
        blimp::PhongMaterial *phongMaterial2;
};

TEST_F(PhongMaterialTest, IsNotNull) {
    ASSERT_NE(phongMaterial, nullptr);
    ASSERT_NE(phongMaterial2, nullptr);
}

TEST_F(PhongMaterialTest, PhongMaterialVertexShaderNotEmpty) {
    ASSERT_TRUE(phongMaterial -> getVertexShader() != NULL);
    ASSERT_NE(phongMaterial -> getVertexShader() -> generateSource() -> length(), 0);
}

TEST_F(PhongMaterialTest, PhongMaterialFragmentShaderNotEmpty) {
    ASSERT_TRUE(phongMaterial -> getFragmentShader() != NULL);
    ASSERT_NE(phongMaterial -> getFragmentShader() -> generateSource() -> length(), 0);
}

TEST_F(PhongMaterialTest, ParametersCorrect) {
    ASSERT_EQ(
        phongMaterial -> getShininess(),
        32.0f
    );

    ASSERT_EQ(
        phongMaterial -> getSpecular(),
        0.75f
    );

    ASSERT_EQ(
        phongMaterial2 -> getShininess(),
        10.0f
    );

    ASSERT_EQ(
        phongMaterial2 -> getSpecular(),
        0.5f
    );
}

TEST_F(PhongMaterialTest, SetShininess) {
    phongMaterial -> setShininess(64.0f);

    ASSERT_EQ(
        phongMaterial -> getShininess(),
        64.0f
    );
}

TEST_F(PhongMaterialTest, SetSpecularFactor) {
    phongMaterial -> setSpecular(0.2f);

    ASSERT_EQ(
        phongMaterial -> getSpecular(),
        0.2f
    );
}
