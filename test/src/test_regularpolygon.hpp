#include <gtest/gtest.h>
#include "../../src/regularpolygon.hpp"

class RegularPolygonTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        rp3 = new blimp::RegularPolygon(3, 1.0f);
        rp4 = new blimp::RegularPolygon(4, 0.5f);
        rp5 = new blimp::RegularPolygon(5, 1.0f);
        rp6 = new blimp::RegularPolygon(6, 1.0f);
        rp10 = new blimp::RegularPolygon(10, 1.0f);
        rp37 = new blimp::RegularPolygon(37, 1.0f);
        rp100 = new blimp::RegularPolygon(100, 1.0f);
    }

    virtual void TearDown() {
        delete rp3;
        delete rp4;
        delete rp5;
        delete rp6;
        delete rp10;
        delete rp37;
        delete rp100;
    }

    blimp::RegularPolygon *rp3;
    blimp::RegularPolygon *rp4;
    blimp::RegularPolygon *rp5;
    blimp::RegularPolygon *rp6;
    blimp::RegularPolygon *rp10;
    blimp::RegularPolygon *rp37;
    blimp::RegularPolygon *rp100;
};

TEST_F(RegularPolygonTest, ExceptionOnTooFewSides) {
    EXPECT_THROW(blimp::RegularPolygon(2, 1.0f), std::invalid_argument);
}

TEST_F(RegularPolygonTest, IsNotNull) {
    ASSERT_TRUE(rp3 != NULL);
    ASSERT_TRUE(rp4 != NULL);
    ASSERT_TRUE(rp5 != NULL);
    ASSERT_TRUE(rp6 != NULL);
    ASSERT_TRUE(rp10 != NULL);
    ASSERT_TRUE(rp37 != NULL);
    ASSERT_TRUE(rp100 != NULL);
}