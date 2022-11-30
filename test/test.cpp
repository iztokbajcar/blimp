#include "window.hpp"
#include "window.cpp"

int main() {
    GLFWwindow* window = blimp::createWindow(800, 600, "Blimp");
    if (!window) {
        return -1;
    }

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}