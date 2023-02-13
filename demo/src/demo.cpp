#include <iostream>
#include "../../src/cuboid.hpp"
#include "../../src/lambertmaterial.hpp"
#include "../../src/mesh.hpp"
#include "../../src/node.hpp"
#include "../../src/normalmaterial.hpp"
#include "../../src/orthographiccamera.hpp"
#include "../../src/perspectivecamera.hpp"
#include "../../src/phongmaterial.hpp"
#include "../../src/pointlight.hpp"
#include "../../src/window.hpp"

#define PI 3.14159265358979323846f

using namespace blimp;

class DemoWindow : public Window {
    public:
        DemoWindow(const char *title, int width, int height) : Window(title, width, height) {}
        void update() {
            std::vector<Node*>* children = this -> scene -> getChildren();
            
            cube1 -> rotate(0.00f, 0.01f, 0.01f);
            cube2 -> rotate(0.00f, 0.01f, 0.01f);
            cube3 -> rotate(0.00f, 0.01f, 0.01f);
            // floor -> rotate(0.00f, 0.008f, 0.00f);

            if (this -> fpsDisplayThrottle == 10) {
                float fps = this -> getFPS();
                this -> setTitle("BlimpDemo | " + std::to_string(fps) + " FPS");
                this -> fpsDisplayThrottle = 0;
            }
            this -> fpsDisplayThrottle++;

            move();
        }

        Mesh* cube1;
        Mesh* cube2;
        Mesh* cube3;
        Mesh* floor;
        Mesh* wall;
        OrthographicCamera* orthographicCamera;
        PerspectiveCamera* perspectiveCamera;
        Node* cameraGroup;

    private:
        bool wPressed = false;
        bool sPressed = false;
        bool aPressed = false;
        bool dPressed = false;
        bool rPressed = false;
        bool fPressed = false;
        bool upPressed = false;
        bool downPressed = false;
        bool leftPressed = false;
        bool rightPressed = false;
        bool plusPressed = false;
        bool minusPressed = false;

        void keyCallback(int key, int scancode, int action, int mode) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                this -> close();
            }
            if (key == GLFW_KEY_W && action == GLFW_PRESS) {
                this -> wPressed = true;
            }
            if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
                this -> wPressed = false;
            }
            if (key == GLFW_KEY_S && action == GLFW_PRESS) {
                this -> sPressed = true;
            }
            if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
                this -> sPressed = false;
            }
            if (key == GLFW_KEY_A && action == GLFW_PRESS) {
                this -> aPressed = true;
            }
            if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
                this -> aPressed = false;
            }
            if (key == GLFW_KEY_D && action == GLFW_PRESS) {
                this -> dPressed = true;
            }
            if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
                this -> dPressed = false;
            }
            if (key == GLFW_KEY_R && action == GLFW_PRESS) {
                this -> rPressed = true;
            }
            if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
                this -> rPressed = false;
            }
            if (key == GLFW_KEY_F && action == GLFW_PRESS) {
                this -> fPressed = true;
            }
            if (key == GLFW_KEY_F && action == GLFW_RELEASE) {
                this -> fPressed = false;
            }
            if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
                this -> upPressed = true;
            }
            if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
                this -> upPressed = false;
            }
            if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
                this -> downPressed = true;
            }
            if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
                this -> downPressed = false;
            }
            if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
                this -> leftPressed = true;
            }
            if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
                this -> leftPressed = false;
            }
            if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
                this -> rightPressed = true;
            }
            if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
                this -> rightPressed = false;
            }
            if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
                this -> plusPressed = true;
            }
            if (key == GLFW_KEY_KP_ADD && action == GLFW_RELEASE) {
                this -> plusPressed = false;
            }
            if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) {
                this -> minusPressed = true;
            }
            if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_RELEASE) {
                this -> minusPressed = false;
            }

            if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
                if (camera == perspectiveCamera)
                    setCamera(orthographicCamera);
                else {
                    setCamera(perspectiveCamera);
                }
            }
        }

        void move() {
            if (this -> wPressed) {
                this -> cameraGroup -> translate(0.0f, 0.0f, -0.1f);
            }
            if (this -> sPressed) {
                this -> cameraGroup -> translate(0.0f, 0.0f, 0.1f);
            }
            if (this -> aPressed) {
                this -> cameraGroup -> translate(-0.1f, 0.0f, 0.0f);
            }
            if (this -> dPressed) {
                this -> cameraGroup -> translate(0.1f, 0.0f, 0.0f);
            }
            if (this -> rPressed) {
                this -> cameraGroup -> translate(0.0f, 0.1f, 0.0f);
            }
            if (this -> fPressed) {
                this -> cameraGroup -> translate(0.0f, -0.1f, 0.0f);
            }
            if (this -> upPressed) {
                this -> cameraGroup -> rotate(0.05f, 0.0f, 0.0f);
            }
            if (this -> downPressed) {
                this -> cameraGroup -> rotate(-0.05f, 0.0f, 0.0f);
            }
            if (this -> leftPressed) {
                this -> cameraGroup -> rotate(0.0f, 0.05f, 0.0f);
            }
            if (this -> rightPressed) {
                this -> cameraGroup -> rotate(0.0f, -0.05f, 0.0f);
            }
            if (this -> plusPressed && this -> camera -> getType() == Node::NODE_TYPE_PERSPECTIVE_CAMERA) {
                PerspectiveCamera* pc = (PerspectiveCamera*)this -> camera;
                pc -> setFov(pc -> getFov() + 1.0f);
            }
            if (this -> minusPressed && this -> camera -> getType() == Node::NODE_TYPE_PERSPECTIVE_CAMERA) {
                PerspectiveCamera* pc = (PerspectiveCamera*)this -> camera;
                pc -> setFov(pc -> getFov() - 1.0f);
            }
        }

        float fpsDisplayThrottle = 0;
};

int main() {
    DemoWindow* window = new DemoWindow("BlimpDemo", 800, 600);
    Node* scene = new Node();

    window -> cameraGroup = new Node();
    window -> orthographicCamera = new OrthographicCamera(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 1000.0f);
    window -> perspectiveCamera = new PerspectiveCamera(60.0f, 800.0f/600.0f, 0.1f, 100.0f);
    window -> cameraGroup -> addChild(window -> orthographicCamera);
    window -> cameraGroup -> addChild(window -> perspectiveCamera);

    ColorVector colors {
        Color(Color::WHITE)
    };

    Material* mat1 = new Material();
    NormalMaterial* mat2 = new NormalMaterial();
    PhongMaterial* mat3 = new PhongMaterial(10.0f, 1.0f);
    LambertMaterial* mat4 = new LambertMaterial();

    window -> cube1 = new Mesh(new Cuboid(1, 1, 1), mat1);
    window -> cube2 = new Mesh(new Cuboid(1, 1, 1), mat2);
    window -> cube3 = new Mesh(new Cuboid(1, 1, 1, &colors), mat3);
    Mesh* floor = new Mesh(new Cuboid(20, 0.1, 20, &colors), mat3);
    Mesh* wall = new Mesh(new Cuboid(5, 2, 0.1, &colors), mat4);
    Mesh* wall2 = new Mesh(new Cuboid(20, 10, 0.1, &colors), mat4);
    window -> cube1 -> setTranslation(-2,  2, -7);
    window -> cube2 -> setTranslation( 2,  2, -7);
    window -> cube3 -> setTranslation(-2, -2, -7);
    floor -> setTranslation(0, -3, -9);
    wall -> setTranslation(3, -1.95, -10);
    wall2 -> setTranslation(25, 0, -20);
    scene -> addChild(window -> cube1);
    scene -> addChild(window -> cube2);
    scene -> addChild(window -> cube3);
    scene -> addChild(floor);
    scene -> addChild(wall);
    scene -> addChild(wall2);

    // lights
    AmbientLight* ambientLight = new AmbientLight(Color(Color::WHITE), 0.1f);
    scene -> addChild(ambientLight);

    DirectionalLight* directionalLight = new DirectionalLight(Color(Color::WHITE), 0.75f);
    directionalLight -> setTranslation(6, 2, 4);
    scene -> addChild(directionalLight);

    PointLight* pointLight = new PointLight(Color(1.0f, 0.5f, 0.0f), 1.0f, 0.8f);
    pointLight -> setTranslation(-3, -1.8, -7);
    scene -> addChild(pointLight);

    PointLight* pointLight2 = new PointLight(Color(Color::FUCHSIA), 1.0f, 1.0f);
    pointLight2 -> setTranslation(4, -0.95, -9);
    scene -> addChild(pointLight2);

    SpotLight* spotLight = new SpotLight(Color(Color::BLUE), 1.0f, 0.9f, 0.85f);
    spotLight -> setTranslation(1, 5, -8);
    spotLight -> setRotation(PI / 2, 0.0f, 0.0f);
    scene -> addChild(spotLight);

    SpotLight* spotLight2 = new SpotLight(Color(Color::LIME), 1.0f, 0.9f, 0.85f);
    spotLight2 -> setTranslation(27, 0, -12);
    spotLight2 -> setRotation(PI, 0.0f, 0.0f);
    scene -> addChild(spotLight2);

    SpotLight* spotLight3 = new SpotLight(Color(Color::RED), 1.0f, 0.9f, 0.85f);
    spotLight3 -> setTranslation(23, 0, -12);
    spotLight3 -> setRotation(PI, 0.0f, 0.0f);
    scene -> addChild(spotLight3);

    window -> setScene(scene);
    window -> setCamera(window -> perspectiveCamera);
    window -> run();
}