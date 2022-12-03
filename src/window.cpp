#include "window.hpp"

blimp::Window::Window(std::string title, int width, int height) {
    this -> width = width;
    this -> height = height;
    this -> title = title;

    // initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);  // hide window initially

    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);  // TODO move into open()?
    glfwSwapInterval(1);

    // initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
    }

    // set viewport
    glViewport(0, 0, width, height);

    this -> window = window;

    // use the default key callback
    this -> setKeyCallback(this, &defaultKeyCallback);

    while (!glfwWindowShouldClose(this -> window)) {
        glfwPollEvents();
        glfwSwapBuffers(this -> window);
    }

    glfwTerminate();
}

void blimp::Window::setKeyCallback(blimp::Window *t, GLFWkeyfun callback) {
    glfwSetKeyCallback(t -> window, callback);
}

void blimp::Window::defaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        std::cout << "Closing window" << std::endl;
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}