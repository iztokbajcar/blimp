#include <gtest/gtest.h>
#include "../src/window.cpp"

class WindowTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            window = new blimp::Window();
        }

        virtual void TearDown() {
            delete window;
        }

        blimp::Window *window;
};

TEST_F(WindowTest, WindowIsNotNull) {
    ASSERT_NE(window, nullptr);
}

TEST_F(WindowTest, WindowIsNotNullAfterOpen) {
    window -> open();
    ASSERT_NE(window, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}