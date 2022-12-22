#ifndef _blimp_WINDOW
#define _blimp_WINDOW

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>

#include "camera.hpp"
#include "node.hpp"

namespace blimp {

    class Window {
        public:
            Window(std::string title = std::string("Blimp"), int width = 800, int height = 600);
            glm::mat4 getProjectionMatrix();
            void setKeyCallback(blimp::Window *t, GLFWkeyfun callback);
            void setScene(Node* scene);
            void setCamera(Camera* camera);
            void render(Node* scene, Camera* camera);
            void run();

        private:
            int width;
            int height;
            std::string title; 
            static void defaultKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
            GLFWwindow* window = nullptr;

            GLuint compileMaterial(Material* material);
            std::map<Material*, GLuint> programs;  // stores the compiled programs for each material
            std::map<Material*, std::vector<Node*>> sortNodesByMaterial(Node* root);  // will be used for speeding up the render process by reducing the number of glUseProgram calls

            Node* scene = nullptr;
            Camera* camera = nullptr;
    };

}

#endif