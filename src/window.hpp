#ifndef _blimp_WINDOW
#define _blimp_WINDOW

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

namespace blimp {

    class Window {
        public:
            Window(std::string title = std::string("Blimp"), int width = 800, int height = 600);
            void setKeyCallback(blimp::Window *t, GLFWkeyfun callback);

        private:
            int width;
            int height;
            std::string title; 
            static void defaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
            GLFWwindow* window = nullptr;
    };

}

#endif