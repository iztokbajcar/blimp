#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace blimp {
    GLFWwindow* createWindow(int width, int height, const char* title);
}