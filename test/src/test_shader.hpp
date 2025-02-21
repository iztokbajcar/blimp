#include <gtest/gtest.h>
#include "../../src/shader.hpp"

class ShaderTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        shader = new blimp::Shader();
    }

    virtual void TearDown() {
        delete shader;
    }

    blimp::Shader *shader;
};

TEST_F(ShaderTest, IsNotNull) {
    ASSERT_NE(shader, nullptr);
}

TEST_F(ShaderTest, SourceNotEmpty) {
    ASSERT_NE(shader -> generateSource() -> length(), 0);
}