#include <gtest/gtest.h>

#include "../../src/ambientlight.hpp"
#include "../../src/camera.hpp"
#include "../../src/cubemap.hpp"
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
        class BrokenVertexShader : public blimp::VertexShader {
            public:
                std::string generateMain() {
                    return "broken";
                }
        };

        class BrokenFragmentShader : public blimp::FragmentShader {
            public:
                std::string generateMain() {
                    return "broken";
                }
        };

        virtual void SetUp() {
            // window = new blimp::Window("BlimpTest");
            texture = new blimp::Texture2D("demo/assets/textures/blimp.png");
            px = new blimp::Texture2D("demo/assets/textures/skybox/px.png");
            nx = new blimp::Texture2D("demo/assets/textures/skybox/nx.png");
            py = new blimp::Texture2D("demo/assets/textures/skybox/py.png");
            ny = new blimp::Texture2D("demo/assets/textures/skybox/ny.png");
            pz = new blimp::Texture2D("demo/assets/textures/skybox/pz.png");
            nz = new blimp::Texture2D("demo/assets/textures/skybox/nz.png");
            
            brokenVS = new BrokenVertexShader();
            workingVS = new blimp::VertexShader();
            brokenFS = new BrokenFragmentShader();
            workingFS = new blimp::FragmentShader();
            brokenVSMaterial = new blimp::Material(brokenVS, workingFS);
            brokenFSMaterial = new blimp::Material(workingVS, brokenFS);

            cubemap = new blimp::Cubemap(px, nx, py, ny, pz, nz);
            scene = new blimp::Scene();
            scene2 = new blimp::Scene();
            scene3 = new blimp::Scene();
            scene4 = new blimp::Scene();
            cube = new blimp::Mesh(new blimp::Cuboid(1, 1, 1), new blimp::LambertMaterial());
            cube3 = new blimp::Mesh(new blimp::Cuboid(1, 1, 1), brokenVSMaterial);
            cube4 = new blimp::Mesh(new blimp::Cuboid(1, 1, 1), brokenFSMaterial);
            camera = new blimp::PerspectiveCamera(80.0f, 800.0f/600.0f, 0.1f, 100.0f);
            ambientLight = new blimp::AmbientLight();
            directionalLight = new blimp::DirectionalLight();
            pointLight = new blimp::PointLight();
            spotLight = new blimp::SpotLight();

            cube -> setTexture(texture);
            scene -> addChild(cube);
            scene -> addChild(ambientLight);
            scene -> addChild(directionalLight);
            scene -> addChild(pointLight);
            scene -> addChild(spotLight);
            scene -> setTexture(texture);
            scene2 -> setTexture(cubemap);
            scene3 -> addChild(cube3);
            scene4 -> addChild(cube4);

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
            this -> window -> setScene(scene2);
            this -> window -> setCamera(camera);

            this -> window2 = new MyTestWindow("BlimpTest2", 800, 600);
            this -> window2 -> setScene(scene);
            this -> window2 -> setCamera(camera);

            this -> window3 = new MyTestWindow("BlimpTest3", 800, 600);
            this -> window3 -> setScene(scene3);
            this -> window3 -> setCamera(camera);

            this -> window4 = new MyTestWindow("BlimpTest4", 800, 600);
            this -> window4 -> setScene(scene4);
            this -> window4 -> setCamera(camera);
        }

        virtual void TearDown() {
            delete window;
            delete window2;
            delete scene;
            delete scene2;
            delete camera;
            delete cube;
            delete texture;
            delete cubemap;
            delete px;
            delete nx;
            delete py;
            delete ny;
            delete pz;
            delete nz;
        }

        blimp::Window *window;
        blimp::Window *window2;
        blimp::Window *window3;
        blimp::Window *window4;
        blimp::Texture2D *texture;
        blimp::Texture2D *px;
        blimp::Texture2D *nx;
        blimp::Texture2D *py;
        blimp::Texture2D *ny;
        blimp::Texture2D *pz;
        blimp::Texture2D *nz;
        blimp::VertexShader *workingVS;
        blimp::VertexShader *brokenVS;
        blimp::FragmentShader *workingFS;
        blimp::FragmentShader *brokenFS;
        blimp::Material *brokenVSMaterial;
        blimp::Material *brokenFSMaterial;
        blimp::Cubemap *cubemap;
        blimp::Mesh *cube;
        blimp::Mesh *cube2;
        blimp::Mesh *cube3;
        blimp::Mesh *cube4;
        blimp::AmbientLight *ambientLight;
        blimp::DirectionalLight *directionalLight;
        blimp::PointLight *pointLight;
        blimp::SpotLight *spotLight;
        blimp::Scene *scene;
        blimp::Scene *scene2;
        blimp::Scene *scene3;
        blimp::Scene *scene4;
        blimp::PerspectiveCamera *camera;
};

TEST_F(WindowTest, IsNotNull) {
    ASSERT_NE(window, nullptr);
    ASSERT_NE(window2, nullptr);
    ASSERT_NE(window3, nullptr);
    ASSERT_NE(window4, nullptr);
}

TEST_F(WindowTest, IsNotNullAfterRun) {
    window -> run();
    ASSERT_NE(window, nullptr);
    window2 -> run();
    ASSERT_NE(window2, nullptr);
}

TEST_F(WindowTest, ExitsOnInvalidVertexShader) {
    ASSERT_EXIT(window3 -> run(),  ::testing::ExitedWithCode(1), "");
}

TEST_F(WindowTest, ExitsOnInvalidFragmentShader) {
    ASSERT_EXIT(window4 -> run(),  ::testing::ExitedWithCode(1), "");
}