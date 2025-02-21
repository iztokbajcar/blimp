#include <gtest/gtest.h>
#include "../../src/regularpyramid.hpp"

class RegularPyramidTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        rp3 = new blimp::RegularPyramid(3, 1.0f);
        rp4 = new blimp::RegularPyramid(4, 0.5f);
        rp5 = new blimp::RegularPyramid(5, 1.0f);
        rp6 = new blimp::RegularPyramid(6, 1.0f);
        rp10 = new blimp::RegularPyramid(10, 1.0f);
        rp37 = new blimp::RegularPyramid(37, 1.0f);
        rp100 = new blimp::RegularPyramid(100, 1.0f);
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

    blimp::RegularPyramid *rp3;
    blimp::RegularPyramid *rp4;
    blimp::RegularPyramid *rp5;
    blimp::RegularPyramid *rp6;
    blimp::RegularPyramid *rp10;
    blimp::RegularPyramid *rp37;
    blimp::RegularPyramid *rp100;
};

TEST_F(RegularPyramidTest, IsNotNull) {
    ASSERT_NE(rp3, nullptr);
    ASSERT_NE(rp4, nullptr);
    ASSERT_NE(rp5, nullptr);
    ASSERT_NE(rp6, nullptr);
    ASSERT_NE(rp10, nullptr);
    ASSERT_NE(rp37, nullptr);
    ASSERT_NE(rp100, nullptr);
}