#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include "../../src/ambientlight.hpp"
#include "../../src/color.hpp"
#include "../../src/cuboid.hpp"
#include "../../src/lambertmaterial.hpp"
#include "../../src/material.hpp"
#include "../../src/mesh.hpp"
#include "../../src/node.hpp"
#include "../../src/normalmaterial.hpp"
#include "../../src/perspectivecamera.hpp"
#include "../../src/phongmaterial.hpp"
#include "../../src/window.hpp"

//////////////////// Ambient light ////////////////////

class AmbientLightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            ambientLight = new blimp::AmbientLight();
            ambientLight2 = new blimp::AmbientLight(blimp::Color(blimp::Color::PURPLE), 0.77f);
        }

        virtual void TearDown() {
            delete ambientLight;
            delete ambientLight2;
        }

        blimp::AmbientLight *ambientLight;
        blimp::AmbientLight *ambientLight2; 
        blimp::Color* white = new blimp::Color(blimp::Color::WHITE);
        blimp::Color* purple = new blimp::Color(blimp::Color::PURPLE);
};

TEST_F(AmbientLightTest, IsNotNull) {
    ASSERT_TRUE(ambientLight != NULL);
    ASSERT_TRUE(ambientLight2 != NULL);
}

TEST_F(AmbientLightTest, IsCorrectType) {
    std::cout << blimp::Node::NODE_TYPE_AMBIENT_LIGHT << std::endl;
    ASSERT_TRUE(ambientLight -> getType() ==blimp::Node::NODE_TYPE_AMBIENT_LIGHT);
    ASSERT_TRUE(ambientLight2 -> getType() == blimp::Node::NODE_TYPE_AMBIENT_LIGHT);
}

TEST_F(AmbientLightTest, IsCorrectColor) {
    blimp::Color* c1 = ambientLight -> getColor();
    blimp::Color* c2 = ambientLight2 -> getColor();
    ASSERT_EQ(c1 -> getR(), white -> getR());
    ASSERT_EQ(c1 -> getG(), white -> getG());
    ASSERT_EQ(c1 -> getB(), white -> getB());

    ASSERT_EQ(c2 -> getR(), purple -> getR());
    ASSERT_EQ(c2 -> getG(), purple -> getG());
    ASSERT_EQ(c2 -> getB(), purple -> getB());
}

TEST_F(AmbientLightTest, IsCorrectIntensity) {
    ASSERT_EQ(ambientLight -> getIntensity(), 1.0f);
    ASSERT_EQ(ambientLight2 -> getIntensity(), 0.77f);
}

//////////////////// Color ////////////////////

class ColorTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            color = new blimp::Color();
            color2 = new blimp::Color(blimp::Color::PURPLE);
            color3 = new blimp::Color(0.1f, 0.2f, 0.3f);
            color4 = new blimp::Color(0.1f, 0.2f, 0.3f, 0.4f);
        }

        virtual void TearDown() {
            delete color;
            delete color2;
            delete color3;
            delete color4;
        }

        blimp::Color *color;
        blimp::Color *color2;
        blimp::Color *color3;
        blimp::Color *color4;
};

TEST_F(ColorTest, IsNotNull) {
    ASSERT_TRUE(color != NULL);
    ASSERT_TRUE(color2 != NULL);
    ASSERT_TRUE(color3 != NULL);
    ASSERT_TRUE(color4 != NULL);
}

TEST_F(ColorTest, IsCorrect) {
    ASSERT_EQ(color -> getR(), 0.0f);
    ASSERT_EQ(color -> getG(), 0.0f);
    ASSERT_EQ(color -> getB(), 0.0f);
    ASSERT_EQ(color -> getA(), 1.0f);

    ASSERT_EQ(color2 -> getR(), 0.5f);
    ASSERT_EQ(color2 -> getG(), 0.0f);
    ASSERT_EQ(color2 -> getB(), 0.5f);
    ASSERT_EQ(color2 -> getA(), 1.0f);

    ASSERT_EQ(color3 -> getR(), 0.1f);
    ASSERT_EQ(color3 -> getG(), 0.2f);
    ASSERT_EQ(color3 -> getB(), 0.3f);
    ASSERT_EQ(color3 -> getA(), 1.0f);

    ASSERT_EQ(color4 -> getR(), 0.1f);
    ASSERT_EQ(color4 -> getG(), 0.2f);
    ASSERT_EQ(color4 -> getB(), 0.3f);
    ASSERT_EQ(color4 -> getA(), 0.4f);
}

//////////////////// Cuboid ////////////////////

class CuboidTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            cuboid = new blimp::Cuboid(1, 2, 3);
        }

        virtual void TearDown() {
            delete cuboid;
        }

        blimp::Cuboid *cuboid;
};

TEST_F(CuboidTest, IsCenteredAtOrigin) {
    GLfloat* verts = cuboid -> getVertices();
    int vertCount = cuboid -> getVertexCount();

    GLfloat sum = 0.0f;

    for (int i = 0; i < vertCount; i++) {
        sum += verts[i];
    }

    ASSERT_EQ(sum, 0);
}

//////////////////// Material ////////////////////

class MaterialTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            material = new blimp::Material();
        }

        virtual void TearDown() {
            delete material;
        }

        blimp::Material *material;
};

TEST_F(MaterialTest, ShadersConstructor) {
    std::string vertexShaderSource = "vertex shader source";
    std::string fragmentShaderSource = "fragment shader source";

    material = new blimp::Material(
        &vertexShaderSource,
        &fragmentShaderSource
    );

    ASSERT_EQ(
        (*material -> getVertexShader()),
        "vertex shader source"
    );

    ASSERT_EQ(
        (*material -> getFragmentShader()),
        "fragment shader source"
    );
}

//////////////////// Node ////////////////////

class NodeTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            node = new blimp::Node();
        }

        virtual void TearDown() {
            delete node;
        }

        blimp::Node *node;
};

TEST_F(NodeTest, Translation) {
    node -> setTranslation(1.0f, 2.0f, 3.0f);

    ASSERT_EQ(
        node -> getTranslation(),
        glm::vec3(1.0f, 2.0f, 3.0f)
    );
}

TEST_F(NodeTest, Rotation) {
    node -> setRotation(4.0f, 5.0f, 6.0f);

    ASSERT_EQ(
        node -> getRotation(),
        glm::quat(glm::vec3(4.0f, 5.0f, 6.0f))
    );
}

TEST_F(NodeTest, Scale) {
    node -> setScale(7.0f, 8.0f, 9.0f);

    ASSERT_EQ(
        node -> getScale(),
        glm::vec3(7.0f, 8.0f, 9.0f)
    );
}

TEST_F(NodeTest, ForwardDirection) {
    node -> setRotation(0.0f, 0.0f, 0.0f);

    ASSERT_EQ(
        node -> getForwardDirection(),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    node -> setRotation(0.0f, glm::half_pi<float>(), 0.0f);
    // node -> setRotation(0.0f, 3.1415926535897932384626433f / 2, 0.0f);

    std::cout << glm::to_string(node -> getForwardDirection()) << std::endl;
    std::cout << glm::to_string(glm::vec3(1.0f, 0.0f, 0.0f)) << std::endl;

    ASSERT_LT(
        node -> getForwardDirection().z - glm::vec3(1.0f, 0.0f, 0.0f).z,
        1e-7f
    );
}

TEST_F(NodeTest, TransformationMatrix) {
    glm::mat4 testMatrix = glm::mat4(1.0f);
    // scale
    testMatrix[0][0] = 2.0f;  // [col][row]
    testMatrix[1][1] = 2.0f;
    testMatrix[2][2] = 2.0f;
    // translate
    testMatrix[3][0] = 1.0f;
    testMatrix[3][1] = 2.0f;
    testMatrix[3][2] = 3.0f;

    node -> setTranslation(1.0f, 2.0f, 3.0f);
    node -> setScale(2.0f, 2.0f, 2.0f);

    ASSERT_EQ(
        node -> getTransformationMatrix(),
        testMatrix
    );
}

TEST_F(NodeTest, ParentTransformationMatrix) {
    node -> setTranslation(1.0f, 2.0f, 3.0f);
    
    blimp::Node* child = new blimp::Node();
    node -> addChild(child); 

    glm::mat4 testMatrix = glm::mat4(1.0f);
    // translate
    testMatrix[3][0] = 1.0f;
    testMatrix[3][1] = 2.0f;
    testMatrix[3][2] = 3.0f;

    ASSERT_EQ(
        child -> getParentTransformationMatrix(),
        testMatrix
    );
}

TEST_F(NodeTest, Children) {
    ASSERT_EQ(
        node -> getChildren() -> size(),
        0
    );

    blimp::Node* child1 = new blimp::Node();
    blimp::Node* child2 = new blimp::Node();
    blimp::Node* grandchild = new blimp::Node();
    node -> addChild(child1);
    node -> addChild(child2);
    child1 -> addChild(grandchild);

    ASSERT_EQ(
        node -> getChildren() -> size(),
        2
    );

    ASSERT_EQ(
        child1 -> getChildren() -> size(),
        1
    );

    ASSERT_EQ(
        child2 -> getChildren() -> size(),
        0
    );

    node -> removeChild(child1);

    ASSERT_EQ(
        child1 -> getChildren() -> size(),
        1
    );

    ASSERT_EQ(
        node -> getChildren() -> size(),
        1
    );

    delete child1;
    delete child2;
}

//////////////////// PerspectiveCamera ////////////////////

class PerspectiveCameraTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            perspectiveCamera = new blimp::PerspectiveCamera(45.0f, 1.0f, 0.1f, 100.0f);
        }

        virtual void TearDown() {
            delete perspectiveCamera;
        }

        blimp::PerspectiveCamera *perspectiveCamera;
};

TEST_F(PerspectiveCameraTest, ViewMatrixIsCorrect) {
    glm::mat4 viewMatrix = perspectiveCamera -> getViewMatrix();

    ASSERT_EQ(
        viewMatrix, 
        glm::inverse(glm::mat4(1.0f))
    );
}

TEST_F(PerspectiveCameraTest, ParametersAreCorrect) {
    ASSERT_EQ(
        perspectiveCamera -> getFov(),
        45.0f
    );

    ASSERT_EQ(
        perspectiveCamera -> getAspect(),
        1.0f
    );

    ASSERT_EQ(
        perspectiveCamera -> getNear(),
        0.1f
    );

    ASSERT_EQ(
        perspectiveCamera -> getFar(),
        100.0f
    );
}

TEST_F(PerspectiveCameraTest, SetParameters) {
    perspectiveCamera -> setFov(90.0f);
    perspectiveCamera -> setAspect(2.0f);
    perspectiveCamera -> setNear(0.2f);
    perspectiveCamera -> setFar(200.0f);

    ASSERT_EQ(
        perspectiveCamera -> getFov(),
        90.0f
    );

    ASSERT_EQ(
        perspectiveCamera -> getAspect(),
        2.0f
    );

    ASSERT_EQ(
        perspectiveCamera -> getNear(),
        0.2f
    );

    ASSERT_EQ(
        perspectiveCamera -> getFar(),
        200.0f
    );
}

//////////////////// PhongMaterial ////////////////////

class LambertMaterialTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            lambertMaterial = new blimp::LambertMaterial();
        }

        virtual void TearDown() {
            delete lambertMaterial;
        }

        blimp::LambertMaterial *lambertMaterial;
};

TEST_F(LambertMaterialTest, IsNotNull) {
    ASSERT_NE(lambertMaterial, nullptr);
}

//////////////////// Window ////////////////////

class WindowTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            // window = new blimp::Window("BlimpTest");
            scene = new blimp::Node();
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
        }

        blimp::Window *window;
        blimp::Node *scene;
        blimp::PerspectiveCamera *camera;
};

TEST_F(WindowTest, IsNotNull) {
    ASSERT_NE(window, nullptr);
}

TEST_F(WindowTest, IsNotNullAfterRun) {
    window -> run();
    ASSERT_NE(window, nullptr);
}

//////////////////////////////////////////////

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 