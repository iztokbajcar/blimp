#include <gtest/gtest.h>
#include "../../src/material.hpp"

class MaterialTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            material = new blimp::Material();
            material -> setShininess(0.3f);
            material2 = new blimp::Material();
            material2 -> setSpecular(0.5f);
            material2 -> setUsesLights(true);
        }

        virtual void TearDown() {
            delete material;
            delete material2;
        }

        blimp::Material *material;
        blimp::Material *material2;
};

TEST_F(MaterialTest, IsNotNull) {
    ASSERT_TRUE(material != NULL);
    ASSERT_TRUE(material2 != NULL);
}

TEST_F(MaterialTest, IsCorrectUsesLights) {
    ASSERT_FALSE(material -> usesLights());
    ASSERT_TRUE(material2 -> usesLights());
}

TEST_F(MaterialTest, ShadersConstructor) {
    blimp::VertexShader* vertexShader = new blimp::VertexShader();
    blimp::FragmentShader* fragmentShader = new blimp::FragmentShader();

    blimp::Material* material = new blimp::Material(
        vertexShader,
        fragmentShader
    );

    ASSERT_EQ(
        material -> getVertexShader(),
        vertexShader
    );

    ASSERT_EQ(
        material -> getFragmentShader(),
        fragmentShader
    );
}

TEST_F(MaterialTest, CorrectShininess) {
    ASSERT_EQ(
        material -> getShininess(),
        0.3f
    );

    ASSERT_EQ(
        material2 -> getShininess(),
        32.0f
    );
}

TEST_F(MaterialTest, CorrectSpecular) {
    ASSERT_EQ(
        material -> getSpecular(),
        0.75f
    );

    ASSERT_EQ(
        material2 -> getSpecular(),
        0.5f
    );
}

