#include <gtest/gtest.h>

#include "../../src/ambientlight.hpp"
#include "../../src/camera.hpp"
#include "../../src/cuboid.hpp"
#include "../../src/directionallight.hpp"
#include "../../src/lambertmaterial.hpp"
#include "../../src/mesh.hpp"
#include "../../src/normalmaterial.hpp"
#include "../../src/perspectivecamera.hpp"
#include "../../src/pointlight.hpp"
#include "../../src/scene.hpp"
#include "../../src/shader.hpp"
#include "../../src/spotlight.hpp"
#include "../../src/window.hpp"


class WindowTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            // window = new blimp::Window("BlimpTest");
            texture = new blimp::Texture2D("demo/assets/textures/blimp.png");
            scene = new blimp::Scene();
            cube = new blimp::Mesh(new blimp::Cuboid(1, 1, 1), new blimp::LambertMaterial());
            cube -> setTexture(texture);
            scene -> addChild(cube);
            camera = new blimp::PerspectiveCamera(80.0f, 800.0f/600.0f, 0.1f, 100.0f);

            class MyTestWindow : public blimp::Window {
                public:
                    MyTestWindow(const char *title, int width, int height) : blimp::Window(title, width, height) {}
                    void update() {
                        float fps = this -> getFPS();
                        this -> setTitle("BlimpTest | " + std::to_string(fps) + " FPS");
                        this -> frameCounter++;

                        if (this -> frameCounter == 10) {
                            this -> close();
                        }
                    }

                protected:
                    void keyCallback(int key, int scancode, int action, int mode) {
                        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                            glfwSetWindowShouldClose(this -> window, GL_TRUE);
                        }
                    }

                private:
                    int frameCounter = 0;
            };

            this -> window = new MyTestWindow("BlimpTest", 800, 600);
            this -> window -> setScene(scene);
            this -> window -> setCamera(camera);
        }

        virtual void TearDown() {
            delete window;
            delete scene;
            delete camera;
            delete cube;
            delete texture;
        }

        blimp::Window *window;
        blimp::Texture2D *texture;
        blimp::Mesh *cube;
        blimp::Scene *scene;
        blimp::PerspectiveCamera *camera;
};

TEST_F(WindowTest, IsNotNull) {
    ASSERT_NE(window, nullptr);
}

TEST_F(WindowTest, IsNotNullAfterRun) {
    window -> run();
    // ASSERT_NE(window, nullptr);
}