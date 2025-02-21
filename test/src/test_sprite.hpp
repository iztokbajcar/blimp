#include <gtest/gtest.h>
#include "../../src/geometry.hpp"
#include "../../src/material.hpp"
#include "../../src/sprite.hpp"

class SpriteTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            geometry = new blimp::Geometry();
            material = new blimp::Material();
            sprite = new blimp::Sprite();
            sprite2 = new blimp::Sprite(geometry, material);
        }

        virtual void TearDown() {
            delete sprite;
            delete sprite2;
            delete geometry;
            delete material;
        }

        blimp::Geometry *geometry;
        blimp::Material *material;
        blimp::Sprite *sprite;
        blimp::Sprite *sprite2;
};

TEST_F(SpriteTest, IsNotNull) {
    ASSERT_NE(sprite, nullptr);
    ASSERT_NE(sprite2, nullptr);
}