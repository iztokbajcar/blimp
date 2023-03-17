#ifndef _blimp_WINDOW
#define _blimp_WINDOW

#define GLEW_STATIC
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>

#include "camera.hpp"
#include "lightsdata.hpp"
#include "mesh.hpp"

/** @file window.hpp */

/** A Map of Material objects and their respective shader programs. */
typedef std::map<blimp::Material*, GLuint> ProgramMap;

/** A Map that assigns a texture unit index to each texture. */
typedef std::map<blimp::Texture*, GLuint> TextureMap;

/** A Map that to each Material assigns a vector of Mesh objects that use the material. */
typedef std::map<blimp::Material*, std::vector<blimp::Mesh*>> MatMeshMap;

/** A pair of a Material and a vector of Mesh objects that use the material. */
typedef std::pair<blimp::Material*, std::vector<blimp::Mesh*>> MatMeshPair;

namespace blimp {

    //! A window, inside which the graphics will be rendered.
    class Window {
        public:
            /** Creates a window with the given title and dimensions.
             * @param title The title of the window
             * @param width The width of the window
             * @param height The height of the window
             */
            Window(std::string title = std::string("Blimp"), int width = 800, int height = 600);

            /** A function that is called immediately after the window is run. 
             * Should be used for initialization of variables.
             * This function should be overridden by the user to implement the desired behavior.
            */
            virtual void init();

            /** A function that is called before each frame is rendered.
             * This function should be overridden by the user to implement the desired behavior.
             */
            virtual void update();

            /** Sets the title of the window. 
             * @param title The new title of the window
            */
            void setTitle(std::string title);

            /** Sets the scene that will be rendered in the window.
             * @param scene The scene
            */
            void setScene(Node* scene);

            /** Sets the camera that will be used to render the scene.
             * @param camera The camera
            */
            void setCamera(Camera* camera);

            /** Displays the window and starts the rendering loop. 
             */
            void run();

            /** Closes the window.
             */
            void close();

            /** Returns the number of frames per seconds at which the window is rendering graphics.
             * @param smoothingFactor The smoothing factor to use when calculating the FPS. The higher the value, the more the FPS will be smoothed.
             * @return The number of frames per seconds
            */
            float getFPS(float smoothingFactor = 0.9);

        protected:
            int width;  /**< The window width. */
            int height;  /**< The window height. */
            std::string title;  /**< The window title. */

            /** A function that is called when a key is pressed.
             * This function should be overridden by the user to implement the desired behavior.
             * @param key The key that was pressed
             * @param scancode The scancode of the key that was pressed
             * @param action The action that was performed on the key
             * @param mode The modifier keys that were pressed
             */
            virtual void keyCallback(int key, int scancode, int action, int mode);

            /**
             * A function that is called when the window's framebuffer is resized.
             * This function should be overridden by the user to implement the desired behavior.
             * @param width The new width of the framebuffer
             * @param height The new height of the framebuffer
             */
            virtual void fbSizeCallback(int width, int height);

            /** Compiles the shader program for the given material.
             * @param material The material
             * @return GLuint The ID of the compiled shader program
             */
            GLuint compileMaterial(Material* material);

            /** Loads the texture and assigns it a texture unit on the GPU.
             * @param texture The texture
             * @return GLuint The texture unit index
            */
            GLuint loadTexture(Texture* texture);

            /** Finds the lights in the given vector of nodes.
             * @param nodes The vector of nodes
             * @return LightsData The lights data
             */
            LightsData getLights(std::vector<Node*>* nodes);

            /** Group the given vector of nodes by material.
             * It is used for speeding up the render process by potentially reducing the number of necessary glUseProgram calls.
             * @param nodes The vector of nodes
             * @return MatMeshMap The map that to each Material assigns a vector of Mesh objects that use the material
             */
            MatMeshMap groupMeshesByMaterial(std::vector<Node*>* nodes);

            /** Updates the viewport size based on the size of the window.
             * 
             */
            void updateViewport();

            ProgramMap programs;  /**< The compiled programs for each material. */
            TextureMap textures;  /**< The texture unit index for each texture. */
            Node* scene = nullptr;  /**< The scene that will be rendered. */
            Camera* camera = nullptr;  /**< The camera that will be used to render the scene. */
            GLFWwindow* window = nullptr;  /**< The GLFW window inside which the graphics will be rendered. */
            void* winUserPointer = nullptr;  /**< The user pointer of the GLFW window. */

            uint64_t lastFrameTime = 0;  /**< The timestamp of the last render. */
            float previousFramesPerSecond = 0;  /**< The previous FPS value (used for smoothing). */
            float currentFramesPerSecond = 0;  /**< The current FPS value. */

        private:
            void render(Node* scene, Camera* camera);
            static void keyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mode);
            static void fbSizeCallbackWrapper(GLFWwindow* window, int width, int height);
            void setKeyCallback(blimp::Window *t, GLFWkeyfun callback);
            void setFbSizeCallback(blimp::Window *t, GLFWwindowsizefun callback);
    };

}

#endif