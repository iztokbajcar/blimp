#include <iostream>
#include "../../src/cuboid.hpp"
#include "../../src/fragmentshader.hpp"
#include "../../src/lambertmaterial.hpp"
#include "../../src/mesh.hpp"
#include "../../src/node.hpp"
#include "../../src/normalmaterial.hpp"
#include "../../src/orthographiccamera.hpp"
#include "../../src/perspectivecamera.hpp"
#include "../../src/phongmaterial.hpp"
#include "../../src/pointlight.hpp"
#include "../../src/regularpolygon.hpp"
#include "../../src/regularprism.hpp"
#include "../../src/regularpyramid.hpp"
#include "../../src/shader.hpp"
#include "../../src/sprite.hpp"
#include "../../src/spritematerial.hpp"
#include "../../src/texture.hpp"
#include "../../src/vertexshader.hpp"
#include "../../src/window.hpp"

#include <glm/gtx/string_cast.hpp>

#define PI 3.14159265358979323846f

using namespace blimp;

class DemoWindow : public Window {
    public:
        DemoWindow(const char *title, int width, int height) : Window(title, width, height) {}

        void init() {
            scene = new Node();

            cameraGroup = new Node();
            orthographicCamera = new OrthographicCamera(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 1000.0f);
            perspectiveCamera = new PerspectiveCamera(60.0f, 800.0f/600.0f, 0.1f, 100.0f);
            cameraGroup -> addChild(orthographicCamera);
            cameraGroup -> addChild(perspectiveCamera);

            ColorVector white {
                Color(Color::WHITE)
            };

            ColorVector red {
                Color(Color::RED)
            };

            bgColor = new Color(Color::TEAL);
            this -> setBackgroundColor(bgColor);

            Texture* blimp = new Texture("demo/assets/textures/blimp.png");
            Texture* bricks = new Texture("demo/assets/textures/bricks.jpg");
            Texture* grass = new Texture("demo/assets/textures/grass.jpg");
            Texture* star = new Texture("demo/assets/textures/star.png");

            Material* mat1 = new Material();
            NormalMaterial* mat2 = new NormalMaterial();
            PhongMaterial* mat3 = new PhongMaterial(10.0f, 1.0f);
            LambertMaterial* mat4 = new LambertMaterial();
            SpriteMaterial* mat5 = new SpriteMaterial();

            //! @todo free allocated stuff when closing

            cube1 = new Mesh(new Cuboid(1, 1, 1, &red), mat1);
            cube2 = new Mesh(new Cuboid(1, 1, 1), mat2);
            cube3 = new Mesh(new Cuboid(1, 1, 1, &white), mat3);
            floor = new Mesh(new Cuboid(50, 0.1, 50, &white), mat4);
            wall = new Mesh(new Cuboid(5, 2, 0.1, &white), mat4);
            wall2 = new Mesh(new Cuboid(5, 5, 0.1, &white), mat4);
            sprite1 = new Sprite(new Rectangle(1.0f, 1.0f), mat5);
            sprite2 = new Sprite(new Rectangle(0.75f, 0.75f), mat5);
            regPoly3 = new Mesh(new RegularPolygon(3, 0.9), mat2);
            regPoly4 = new Mesh(new RegularPolygon(4, 0.9), mat2);
            regPoly5 = new Mesh(new RegularPolygon(5, 0.9), mat2);
            regPoly6 = new Mesh(new RegularPolygon(6, 0.9), mat2);
            regPoly7 = new Mesh(new RegularPolygon(7, 0.9), mat2);
            regPoly8 = new Mesh(new RegularPolygon(8, 0.9), mat2);
            regPrism3 = new Mesh(new RegularPrism(3, 0.9, 0.9), mat2);
            regPrism4 = new Mesh(new RegularPrism(4, 0.9, 0.9), mat2);
            regPrism5 = new Mesh(new RegularPrism(5, 0.9, 0.9), mat2);
            regPrism6 = new Mesh(new RegularPrism(6, 0.9, 0.9), mat2);
            regPrism7 = new Mesh(new RegularPrism(7, 0.9, 0.9), mat2);
            regPrism8 = new Mesh(new RegularPrism(8, 0.9, 0.9), mat2);
            regPyramid3 = new Mesh(new RegularPyramid(3, 0.9, 0.9), mat2);
            regPyramid4 = new Mesh(new RegularPyramid(4, 0.9, 0.9), mat2);
            regPyramid5 = new Mesh(new RegularPyramid(5, 0.9, 0.9), mat2);
            regPyramid6 = new Mesh(new RegularPyramid(6, 0.9, 0.9), mat2);
            regPyramid7 = new Mesh(new RegularPyramid(7, 0.9, 0.9), mat2);
            regPyramid8 = new Mesh(new RegularPyramid(8, 0.9, 0.9), mat2);

            cube3 -> setTexture(blimp);
            floor -> setTexture(grass, new TextureOptions(TextureOptions::REPEAT, TextureOptions::NEAREST));
            floor -> getTextureOptions() -> setScale(0.25f);
            wall -> setTexture(bricks, new TextureOptions(TextureOptions::REPEAT, TextureOptions::LINEAR));
            wall -> getTextureOptions() -> setScale(0.5f, 1.0f);
            wall2 -> setTexture(bricks, new TextureOptions(TextureOptions::REPEAT, TextureOptions::LINEAR));
            wall2 -> getTextureOptions() -> setScale(0.5f);
            sprite1 -> setTexture(star, new TextureOptions(TextureOptions::NEAREST));
            sprite2 -> setTexture(star, new TextureOptions(TextureOptions::NEAREST)); 

            cube1 -> setTranslation(-2,  2, -7);
            cube2 -> setTranslation( 2,  2, -7);
            cube3 -> setTranslation(-2, -2, -7);
            floor -> setTranslation(0, -3, -9);
            wall -> setTranslation(3, -1.95, -10);
            sprite1 -> setTranslation(-9, 3, -16);
            sprite2 -> setTranslation(-9, 3, -15);

            // wall2 -> setTranslation(0, 0, 0);
            scene -> addChild(cube1);
            scene -> addChild(cube2);
            scene -> addChild(cube3);
            scene -> addChild(floor);
            scene -> addChild(wall);
            scene -> addChild(sprite1);
            scene -> addChild(sprite2);

            // lights
            AmbientLight* ambientLight = new AmbientLight(Color(Color::WHITE), 0.2f);
            scene -> addChild(ambientLight);

            DirectionalLight* directionalLight = new DirectionalLight(Color(Color::WHITE), 1.0f);
            directionalLight -> setTranslation(6, 2, 4);
            scene -> addChild(directionalLight);

            PointLight* pointLight = new PointLight(Color(1.0f, 0.5f, 0.0f), 1.0f, 0.8f);
            pointLight -> setTranslation(-3, -1.8, -7);
            scene -> addChild(pointLight);

            PointLight* pointLight2 = new PointLight(Color(Color::FUCHSIA), 1.0f, 1.0f);
            pointLight2 -> setTranslation(4, -0.95, -9);
            scene -> addChild(pointLight2);

            SpotLight* spotLight = new SpotLight(Color(Color::AQUA), 1.0f, 0.9f, 0.85f);
            spotLight -> setTranslation(1, 5, -8);
            spotLight -> setRotation(PI / 2, 0.0f, 0.0f);
            scene -> addChild(spotLight);

            // spotLight4 -> setTranslation(23, 0, -15);

            colorsNode = new Node();

            SpotLight* spotLight2 = new SpotLight(Color(Color::LIME), 1.0f, 0.85f, 0.85f);
            SpotLight* spotLight3 = new SpotLight(Color(Color::RED), 1.0f, 0.85f, 0.85f);
            SpotLight* spotLight4 = new SpotLight(Color(Color::BLUE), 1.0f, 0.85f, 0.85f);
            colorsNode -> addChild(wall2);
            colorsNode -> addChild(spotLight2);
            colorsNode -> addChild(spotLight3);
            colorsNode -> addChild(spotLight4);
            wall2 -> setTranslation(0, 0, -1.25);
            spotLight2 -> setTranslation(-0.75, -0.25, 1.5);
            spotLight3 -> setTranslation(0.75, -0.25, 1.5);
            spotLight4 -> setTranslation(0, 1, 1.5);
            spotLight2 -> setRotation(PI, 0.0f, 0.0f);
            spotLight3 -> setRotation(PI, 0.0f, 0.0f);
            spotLight4 -> setRotation(PI, 0.0f, 0.0f);

            colorsNode -> setTranslation(-5, 0, -20);
            scene -> addChild(colorsNode);

            regPolysNode = new Node();
            regPolysNode -> addChild(regPoly3);
            regPolysNode -> addChild(regPoly4);
            regPolysNode -> addChild(regPoly5);
            regPolysNode -> addChild(regPoly6);
            regPolysNode -> addChild(regPoly7);
            regPolysNode -> addChild(regPoly8);
            regPoly3 -> setTranslation(0, 0, 0);
            regPoly4 -> setTranslation(2, 0, 0);
            regPoly5 -> setTranslation(4, 0, 0);
            regPoly6 -> setTranslation(6, 0, 0);
            regPoly7 -> setTranslation(8, 0, 0);
            regPoly8 -> setTranslation(10, 0, 0);
            regPolysNode -> setTranslation(0, 4, -21.25);
            scene -> addChild(regPolysNode);

            regPrismsNode = new Node();
            regPrismsNode -> addChild(regPrism3);
            regPrismsNode -> addChild(regPrism4);
            regPrismsNode -> addChild(regPrism5);
            regPrismsNode -> addChild(regPrism6);
            regPrismsNode -> addChild(regPrism7);
            regPrismsNode -> addChild(regPrism8);
            regPrism3 -> setTranslation(0, 0, 0);
            regPrism4 -> setTranslation(2, 0, 0);
            regPrism5 -> setTranslation(4, 0, 0);
            regPrism6 -> setTranslation(6, 0, 0);
            regPrism7 -> setTranslation(8, 0, 0);
            regPrism8 -> setTranslation(10, 0, 0);
            regPrismsNode -> setTranslation(0, 2, -19.25);
            scene -> addChild(regPrismsNode);

            regPyramidsNode = new Node();
            regPyramidsNode -> addChild(regPyramid3);
            regPyramidsNode -> addChild(regPyramid4);
            regPyramidsNode -> addChild(regPyramid5);
            regPyramidsNode -> addChild(regPyramid6);
            regPyramidsNode -> addChild(regPyramid7);
            regPyramidsNode -> addChild(regPyramid8);
            regPyramid3 -> setTranslation(0, 0, 0);
            regPyramid4 -> setTranslation(2, 0, 0);
            regPyramid5 -> setTranslation(4, 0, 0);
            regPyramid6 -> setTranslation(6, 0, 0);
            regPyramid7 -> setTranslation(8, 0, 0);
            regPyramid8 -> setTranslation(10, 0, 0);
            regPyramidsNode -> setTranslation(0, 0, -17.25);
            scene -> addChild(regPyramidsNode);

            setScene(scene);
            setCamera(perspectiveCamera);
        }

        void update() {
            std::vector<Node*>* children = this -> scene -> getChildren();
            
            cube1 -> rotate(0.00f, 0.01f, 0.01f);
            cube2 -> rotate(0.00f, 0.01f, 0.01f);
            cube3 -> rotate(0.00f, 0.01f, 0.01f);
            regPyramid3 -> rotate(0.00f, 0.00f, 0.003f);
            regPyramid4 -> rotate(0.00f, 0.00f, 0.003f);
            regPyramid5 -> rotate(0.00f, 0.00f, 0.003f);
            regPyramid6 -> rotate(0.00f, 0.00f, 0.003f);
            regPyramid7 -> rotate(0.00f, 0.00f, 0.003f);
            regPyramid8 -> rotate(0.00f, 0.00f, 0.003f);

            if (this -> fpsDisplayThrottle == 10) {
                float fps = this -> getFPS();
                this -> setTitle("BlimpDemo | " + std::to_string(fps) + " FPS");
                this -> fpsDisplayThrottle = 0;
            }
            this -> fpsDisplayThrottle++;

            move();
        }

        Node* scene;
        Mesh* cube1;
        Mesh* cube2;
        Mesh* cube3;
        Mesh* floor;
        Mesh* wall;
        Mesh* wall2;
        Sprite* sprite1;
        Sprite* sprite2;
        Mesh* regPoly3;
        Mesh* regPoly4;
        Mesh* regPoly5;
        Mesh* regPoly6;
        Mesh* regPoly7;
        Mesh* regPoly8;
        Mesh* regPrism3;
        Mesh* regPrism4;
        Mesh* regPrism5;
        Mesh* regPrism6;
        Mesh* regPrism7;
        Mesh* regPrism8;
        Mesh* regPyramid3;
        Mesh* regPyramid4;
        Mesh* regPyramid5;
        Mesh* regPyramid6;
        Mesh* regPyramid7;
        Mesh* regPyramid8;
        OrthographicCamera* orthographicCamera;
        PerspectiveCamera* perspectiveCamera;
        Node* cameraGroup;
        Node* colorsNode;
        Node* regPolysNode;
        Node* regPyramidsNode;
        Node* regPrismsNode;
        Color* bgColor;

    private:
        bool wPressed = false;
        bool sPressed = false;
        bool aPressed = false;
        bool dPressed = false;
        bool spacePressed = false;
        bool shiftPressed = false;
        bool upPressed = false;
        bool downPressed = false;
        bool leftPressed = false;
        bool rightPressed = false;
        bool plusPressed = false;
        bool minusPressed = false;
        bool firstMouse = true;
        double lastX = 0.0f;
        double lastY = 0.0f;
        double yaw = -90.0f;
        double pitch = 0.0f;
        double mouseSensitivity = 0.01f;

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
            if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
                this -> spacePressed = true;
            }
            if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
                this -> spacePressed = false;
            }
            if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
                this -> shiftPressed = true;
            }
            if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
                this -> shiftPressed = false;
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

            if (key == GLFW_KEY_C && action == GLFW_RELEASE) {
                this -> toggleCursorLock();
            }

            if (key == GLFW_KEY_PERIOD && action == GLFW_RELEASE) {
                this -> toggleWireframeMode();
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
            if (this -> spacePressed) {
                this -> cameraGroup -> translate(0.0f, 0.1f, 0.0f);
            }
            if (this -> shiftPressed) {
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
            if (this -> plusPressed && camera -> getNodeType() == Node::NODE_TYPE_PERSPECTIVE_CAMERA) {
                PerspectiveCamera* pc = (PerspectiveCamera*)this -> camera;
                pc -> setFov(pc -> getFov() + 1.0f);
            }
            if (this -> minusPressed && camera -> getNodeType() == Node::NODE_TYPE_PERSPECTIVE_CAMERA) {
                PerspectiveCamera* pc = (PerspectiveCamera*)this -> camera;
                pc -> setFov(pc -> getFov() - 1.0f);
            }
        }

        void mouseMoveCallback(double xPos, double yPos) {
            if (this -> firstMouse) {
                this -> lastX = xPos;
                this -> lastY = yPos;
                this -> firstMouse = false;
            }

            float xOffset = xPos - this -> lastX;
            float yOffset = this -> lastY - yPos;
            this -> lastX = xPos;
            this -> lastY = yPos;

            // this -> yaw -= xOffset * this -> mouseSensitivity;
            // this -> pitch -= yOffset * this -> mouseSensitivity;

            this -> cameraGroup -> rotate(
                yOffset * this -> mouseSensitivity,
                -xOffset * this -> mouseSensitivity,
                0.0f
            );
        }

        float fpsDisplayThrottle = 0;
};

int main() {
    DemoWindow* window = new DemoWindow("BlimpDemo", 800, 600);
    window -> lockCursor(); 
    window -> run();
}