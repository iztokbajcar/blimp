#include <gtest/gtest.h>
#include "../../src/geometry.hpp"

class GeometryTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            ColorVector* colors = new ColorVector{blimp::Color::RED, blimp::Color::BLUE};
            geometry = new blimp::Geometry();
            geometry2 = new blimp::Geometry(colors);
        }

        virtual void TearDown() {
            delete geometry;
            delete geometry2;
        }

        ColorVector* colors;
        blimp::Geometry* geometry;
        blimp::Geometry* geometry2;
};

TEST_F(GeometryTest, IsNotNull) {
    ASSERT_TRUE(geometry != NULL);
    ASSERT_TRUE(geometry2 != NULL);
}

TEST_F(GeometryTest, IsCorrectColor) {
    ASSERT_TRUE(geometry -> getColors() == NULL);
    ASSERT_TRUE(geometry2 -> getColors() != NULL);
}

TEST_F(GeometryTest, TestGetNormals) {
    ASSERT_TRUE(geometry -> getNormals() == NULL);
    ASSERT_TRUE(geometry2 -> getNormals() == NULL);
}

TEST_F(GeometryTest, TestGetTexCoords) {
    ASSERT_TRUE(geometry -> getTexCoords() == NULL);
    ASSERT_TRUE(geometry2 -> getTexCoords() == NULL);
}