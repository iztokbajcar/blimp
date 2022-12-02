#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace blimp {
    class Window {
        public:
            Window(int width = 800, int height = 600, const char* title = "Blimp");
            void setKeyCallback(blimp::Window *t, GLFWkeyfun callback);
            void open();

        private:
            static void defaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
            GLFWwindow* window = nullptr;
    };
}