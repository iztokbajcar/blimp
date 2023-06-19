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
#include "../../src/orthographiccamera.hpp"
#include "../../src/perspectivecamera.hpp"
#include "../../src/phongmaterial.hpp"
#include "../../src/texture.hpp"
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
    ASSERT_TRUE(ambientLight -> getNodeType() ==blimp::Node::NODE_TYPE_AMBIENT_LIGHT);
    ASSERT_TRUE(ambientLight2 -> getNodeType() == blimp::Node::NODE_TYPE_AMBIENT_LIGHT);
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

//////////////////// DirectionalLight ////////////////////

class DirectionalLightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            directionalLight = new blimp::DirectionalLight();
            directionalLight2 = new blimp::DirectionalLight(blimp::Color(blimp::Color::PURPLE), 0.5f);
        }

        virtual void TearDown() {
            delete directionalLight;
            delete directionalLight2;
        }

        blimp::DirectionalLight *directionalLight;
        blimp::DirectionalLight *directionalLight2; 
        blimp::Color* white = new blimp::Color(blimp::Color::WHITE);
        blimp::Color* purple = new blimp::Color(blimp::Color::PURPLE);
};

TEST_F(DirectionalLightTest, IsNotNull) {
    ASSERT_TRUE(directionalLight != NULL);
    ASSERT_TRUE(directionalLight2 != NULL);
}

TEST_F(DirectionalLightTest, IsCorrectType) {
    ASSERT_TRUE(directionalLight -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
    ASSERT_TRUE(directionalLight2 -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
}

TEST_F(DirectionalLightTest, IsCorrectColor) {
    blimp::Color* c1 = directionalLight -> getColor();
    blimp::Color* c2 = directionalLight2 -> getColor();
    ASSERT_EQ(c1 -> getR(), white -> getR());
    ASSERT_EQ(c1 -> getG(), white -> getG());
    ASSERT_EQ(c1 -> getB(), white -> getB());

    ASSERT_EQ(c2 -> getR(), purple -> getR());
    ASSERT_EQ(c2 -> getG(), purple -> getG());
    ASSERT_EQ(c2 -> getB(), purple -> getB());
}

TEST_F(DirectionalLightTest, IsCorrectIntensity) {
    ASSERT_EQ(directionalLight -> getIntensity(), 1.0f);
    ASSERT_EQ(directionalLight2 -> getIntensity(), 0.5f);
}

//////////////////// Geometry ////////////////////

class GeometryTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            ColorVector* colors = new ColorVector{blimp::Color::RED, blimp::Color::BLUE};
            geometry = new blimp::Geometry();
            geometry2 = new blimp::Geometry(colors);
        }

        virtual void TearDown() {
            delete geometry;
            delete geometry2;
        }

        ColorVector* colors;
        blimp::Geometry* geometry;
        blimp::Geometry* geometry2;
};

TEST_F(GeometryTest, IsNotNull) {
    ASSERT_TRUE(geometry != NULL);
    ASSERT_TRUE(geometry2 != NULL);
}

TEST_F(GeometryTest, IsCorrectColor) {
    ASSERT_TRUE(geometry -> getColors() == NULL);
    ASSERT_TRUE(geometry2 -> getColors() != NULL);
}

//////////////////// Light ////////////////////

class LightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            light = new blimp::Light();
            light2 = new blimp::Light(blimp::Color(blimp::Color::PURPLE), 0.5f);
            light3 = new blimp::Light();
            light3 -> setColor(blimp::Color(blimp::Color::GREEN));
            light3 -> setIntensity(0.2f);
        }

        virtual void TearDown() {
            delete light;
            delete light2;
            delete light3;
        }

        blimp::Light *light;
        blimp::Light *light2; 
        blimp::Light *light3;
        blimp::Color* white = new blimp::Color(blimp::Color::WHITE);
        blimp::Color* purple = new blimp::Color(blimp::Color::PURPLE);
};

TEST_F(LightTest, IsNotNull) {
    ASSERT_TRUE(light != NULL);
    ASSERT_TRUE(light2 != NULL);
    ASSERT_TRUE(light3 != NULL);
}

TEST_F(LightTest, IsCorrectType) {
    ASSERT_TRUE(light -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
    ASSERT_TRUE(light2 -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
    ASSERT_TRUE(light3 -> getNodeType() == blimp::Node::NODE_TYPE_DIRECTIONAL_LIGHT);
}

TEST_F(LightTest, IsCorrectColor) {
    blimp::Color* c1 = light -> getColor();
    blimp::Color* c2 = light2 -> getColor();
    blimp::Color* c3 = light3 -> getColor();

    ASSERT_EQ(c1 -> getR(), white -> getR());
    ASSERT_EQ(c1 -> getG(), white -> getG());
    ASSERT_EQ(c1 -> getB(), white -> getB());

    ASSERT_EQ(c2 -> getR(), purple -> getR());
    ASSERT_EQ(c2 -> getG(), purple -> getG());
    ASSERT_EQ(c2 -> getB(), purple -> getB());

    ASSERT_EQ(c3 -> getR(), 0.0f);
    ASSERT_EQ(c3 -> getG(), 0.5f);
    ASSERT_EQ(c3 -> getB(), 0.0f);
}

TEST_F(LightTest, IsCorrectIntensity) {
    ASSERT_EQ(light -> getIntensity(), 1.0f);
    ASSERT_EQ(light2 -> getIntensity(), 0.5f);
    ASSERT_EQ(light3 -> getIntensity(), 0.2f);
}

//////////////////// Material ////////////////////

class MaterialTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            material = new blimp::Material();
            material2 = new blimp::Material();
            material2 -> setUsesLights(true);
        }

        virtual void TearDown() {
            delete material;
            delete material2;
        }

        blimp::Material *material;
        blimp::Material *material2;
};

TEST_F(MaterialTest, IsNotNull) {
    ASSERT_TRUE(material != NULL);
    ASSERT_TRUE(material2 != NULL);
}

TEST_F(MaterialTest, IsCorrectUsesLights) {
    ASSERT_FALSE(material -> usesLights());
    ASSERT_TRUE(material2 -> usesLights());
}

TEST_F(MaterialTest, ShadersConstructor) {
    std::string vertexShaderSource = "vertex shader source";
    std::string fragmentShaderSource = "fragment shader source";

    blimp::Material* material = new blimp::Material(
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

//////////////////// Mesh ////////////////////

class MeshTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            mesh = new blimp::Mesh();
            mesh2 = new blimp::Mesh();
            geometry = new blimp::Geometry();
            material = new blimp::Material();
            mesh2 -> setGeometry(geometry);
            mesh2 -> setMaterial(material);
            mesh3 = new blimp::Mesh(geometry, material);
        }

        virtual void TearDown() {
            delete mesh;
            delete mesh2;
            delete mesh3;
        }

        blimp::Mesh *mesh;
        blimp::Mesh *mesh2;
        blimp::Mesh *mesh3;
        blimp::Geometry* geometry;
        blimp::Material* material;
};

TEST_F(MeshTest, IsNotNull) {
    ASSERT_TRUE(mesh != NULL);
    ASSERT_TRUE(mesh2 != NULL);
    ASSERT_TRUE(mesh3 != NULL);
}

TEST_F(MeshTest, IsCorrectGeometry) {
    ASSERT_TRUE(mesh -> getGeometry() == NULL);
    ASSERT_TRUE(mesh2 -> getGeometry() == geometry);
    ASSERT_TRUE(mesh3 -> getGeometry() == geometry);
}

TEST_F(MeshTest, IsCorrectMaterial) {
    ASSERT_TRUE(mesh -> getMaterial() == NULL);
    ASSERT_TRUE(mesh2 -> getMaterial() == material);
    ASSERT_TRUE(mesh3 -> getMaterial() == material);
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

    node -> translate(-1.0f, -2.0f, -3.0f);

    ASSERT_EQ(
        node -> getTranslation(),
        glm::vec3(0.0f)
    );
}

TEST_F(NodeTest, Rotation) {   
    node -> setRotation(4.0f, 5.0f, 6.0f);

    ASSERT_EQ(
        glm::to_string(node -> getRotation()),
        "quat(-0.406853, {-0.686041, -0.349363, 0.491695})"
    );

    node -> setRotation(0.0f, 0.0f, 0.0f);
    node -> rotate(1.0f, 2.0f, 3.0f);

    ASSERT_EQ(
        glm::to_string(node -> getRotation()),
        "quat(-0.368871, {-0.754934, 0.206149, -0.501509})"
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

    std::vector<blimp::Node*> vec = node -> traverseChildren();
    
    ASSERT_EQ(
        vec.size(),
        1
    );

    delete child1;
    delete child2;
}

//////////////////// NormalMaterial ////////////////////

class NormalMaterialTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            normalMaterial = new blimp::NormalMaterial();
        }

        virtual void TearDown() {
            delete normalMaterial;
        }

        blimp::NormalMaterial *normalMaterial;
};

TEST_F(NormalMaterialTest, IsNotNull) {
    ASSERT_TRUE(normalMaterial != NULL);
}

//////////////////// OrthographicCamera ////////////////////

class OrthographicCameraTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            orthographicCamera = new blimp::OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
        }

        virtual void TearDown() {
            delete orthographicCamera;
        }

        blimp::OrthographicCamera *orthographicCamera;
};

TEST_F(OrthographicCameraTest, ViewMatrixIsCorrect) {
    glm::mat4 viewMatrix = orthographicCamera -> getViewMatrix();

    ASSERT_EQ(
        viewMatrix, 
        glm::inverse(glm::mat4(1.0f))
    );
}

TEST_F(OrthographicCameraTest, ParametersAreCorrect) {
    ASSERT_EQ(
        orthographicCamera -> getLeft(),
        -1.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getRight(),
        1.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getBottom(),
        -1.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getTop(),
        1.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getNear(),
        0.1f
    );

    ASSERT_EQ(
        orthographicCamera -> getFar(),
        100.0f
    );
}

TEST_F(OrthographicCameraTest, SetParameters) {
    orthographicCamera -> setLeft(-2.0f);
    orthographicCamera -> setRight(2.0f);
    orthographicCamera -> setBottom(-2.0f);
    orthographicCamera -> setTop(2.0f);
    orthographicCamera -> setNear(0.2f);
    orthographicCamera -> setFar(200.0f);

    ASSERT_EQ(
        orthographicCamera -> getLeft(),
        -2.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getRight(),
        2.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getBottom(),
        -2.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getTop(),
        2.0f
    );

    ASSERT_EQ(
        orthographicCamera -> getNear(),
        0.2f
    );

    ASSERT_EQ(
        orthographicCamera -> getFar(),
        200.0f
    );
}

TEST_F(OrthographicCameraTest, ProjectionMatrixIsCorrect) {
    orthographicCamera = new blimp::OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    glm::mat4 projectionMatrix = orthographicCamera -> getProjectionMatrix();

    ASSERT_EQ(
        projectionMatrix,
        glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f)
    );
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

class PhongMaterialTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            phongMaterial = new blimp::PhongMaterial();
            phongMaterial2 = new blimp::PhongMaterial(10.0f, 0.5f);
        }

        virtual void TearDown() {
            delete phongMaterial;
            delete phongMaterial2;
        }

        blimp::PhongMaterial *phongMaterial;
        blimp::PhongMaterial *phongMaterial2;
};

TEST_F(PhongMaterialTest, IsNotNull) {
    ASSERT_NE(phongMaterial, nullptr);
    ASSERT_NE(phongMaterial2, nullptr);
}

TEST_F(PhongMaterialTest, ParametersCorrect) {
    ASSERT_EQ(
        phongMaterial -> getShininess(),
        32.0f
    );

    ASSERT_EQ(
        phongMaterial -> getSpecular(),
        0.75f
    );

    ASSERT_EQ(
        phongMaterial2 -> getShininess(),
        10.0f
    );

    ASSERT_EQ(
        phongMaterial2 -> getSpecular(),
        0.5f
    );
}

TEST_F(PhongMaterialTest, SetShininess) {
    phongMaterial -> setShininess(64.0f);

    ASSERT_EQ(
        phongMaterial -> getShininess(),
        64.0f
    );
}

TEST_F(PhongMaterialTest, SetSpecularFactor) {
    phongMaterial -> setSpecular(0.2f);

    ASSERT_EQ(
        phongMaterial -> getSpecular(),
        0.2f
    );
}

//////////////////// PointLight ////////////////////

class PointLightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            pointLight = new blimp::PointLight();
            pointLight2 = new blimp::PointLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f);
        }

        virtual void TearDown() {
            delete pointLight;
            delete pointLight2;
        }

        blimp::PointLight *pointLight;
        blimp::PointLight *pointLight2;
};

TEST_F(PointLightTest, IsNotNull) {
    ASSERT_NE(pointLight, nullptr);
    ASSERT_NE(pointLight2, nullptr);
}

TEST_F(PointLightTest, TypeIsCorrect) {
    ASSERT_EQ(
        pointLight -> getNodeType(),
        blimp::Node::NODE_TYPE_POINT_LIGHT
    );

    ASSERT_EQ(
        pointLight2 -> getNodeType(),
        blimp::Light::NODE_TYPE_POINT_LIGHT
    );
}

TEST_F(PointLightTest, ColorIsCorrect) {
    blimp::Color* c1 = pointLight -> getColor();
    blimp::Color* c2 = pointLight2 -> getColor();

    ASSERT_EQ(c1 -> getR(), 1.0f);
    ASSERT_EQ(c1 -> getG(), 1.0f);
    ASSERT_EQ(c1 -> getB(), 1.0f);

    ASSERT_EQ(c2 -> getR(), 0.0f);
    ASSERT_EQ(c2 -> getG(), 1.0f);
    ASSERT_EQ(c2 -> getB(), 1.0f);
}

TEST_F(PointLightTest, IntensityIsCorrect) {
    ASSERT_EQ(
        pointLight -> getIntensity(),
        1.0f
    );

    ASSERT_EQ(
        pointLight2 -> getIntensity(),
        0.6f
    );
}

TEST_F(PointLightTest, AttenuationIsCorrect) {
    ASSERT_EQ(
        pointLight -> getAttenuation(),
        1.0f
    );

    ASSERT_EQ(
        pointLight2 -> getAttenuation(),
        0.5f
    );
}

TEST_F(PointLightTest, SetAttenuation) {
    blimp::PointLight* pointLightAttenuationTest = new blimp::PointLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f);
    pointLightAttenuationTest -> setAttenuation(0.2f);

    ASSERT_EQ(
        pointLightAttenuationTest -> getAttenuation(),
        0.2f
    );
}

//////////////////// SpotLight ////////////////////

class SpotLightTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            spotLight = new blimp::SpotLight();
            spotLight2 = new blimp::SpotLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f, 0.2f);
        }

        virtual void TearDown() {
            delete spotLight;
            delete spotLight2;
        }

        blimp::SpotLight *spotLight;
        blimp::SpotLight *spotLight2;
};

TEST_F(SpotLightTest, IsNotNull) {
    ASSERT_NE(spotLight, nullptr);
    ASSERT_NE(spotLight2, nullptr);
}

TEST_F(SpotLightTest, TypeIsCorrect) {
    ASSERT_EQ(
        spotLight -> getNodeType(),
        blimp::Node::NODE_TYPE_SPOT_LIGHT
    );

    ASSERT_EQ(
        spotLight2 -> getNodeType(),
        blimp::Node::NODE_TYPE_SPOT_LIGHT
    );
}

TEST_F(SpotLightTest, ColorIsCorrect) {
    blimp::Color* c1 = spotLight -> getColor();
    blimp::Color* c2 = spotLight2 -> getColor();

    ASSERT_EQ(c1 -> getR(), 1.0f);
    ASSERT_EQ(c1 -> getG(), 1.0f);
    ASSERT_EQ(c1 -> getB(), 1.0f);

    ASSERT_EQ(c2 -> getR(), 0.0f);
    ASSERT_EQ(c2 -> getG(), 1.0f);
    ASSERT_EQ(c2 -> getB(), 1.0f);
}

TEST_F(SpotLightTest, IntensityIsCorrect) {
    ASSERT_EQ(
        spotLight -> getIntensity(),
        1.0f
    );

    ASSERT_EQ(
        spotLight2 -> getIntensity(),
        0.6f
    );
}

TEST_F(SpotLightTest, SetInnerCutoff) {
    blimp::SpotLight* spotLightInnerCutoffTest = new blimp::SpotLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f, 0.2f);
    spotLightInnerCutoffTest -> setInnerCutoff(0.4f);

    ASSERT_EQ(
        spotLightInnerCutoffTest -> getInnerCutoff(),
        0.4f
    );
}

TEST_F(SpotLightTest, SetOuterCutoff) {
    blimp::SpotLight* spotLightOuterCutoffTest = new blimp::SpotLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f, 0.2f);
    spotLightOuterCutoffTest -> setOuterCutoff(0.3f);

    ASSERT_EQ(
        spotLightOuterCutoffTest -> getOuterCutoff(),
        0.3f
    );
}

//////////////////// Texture ////////////////////

class TextureTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            texture = new blimp::Texture("demo/assets/textures/blimp.png");
        }

        virtual void TearDown() {
            delete texture;
        }

        blimp::Texture *texture;
};

TEST_F(TextureTest, IsNotNull) {
    ASSERT_NE(texture, nullptr);
}

TEST_F(TextureTest, WidthCorrect) {
    ASSERT_EQ(texture -> getWidth(), 512);
}

TEST_F(TextureTest, HeightCorrect) {
    ASSERT_EQ(texture -> getHeight(), 512);
}

TEST_F(TextureTest, DataNotNull) {
    ASSERT_NE(texture -> getData(), nullptr);
}

//////////////////// TextureOptions ////////////////////

class TextureOptionsTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            options = new blimp::TextureOptions();
            options2 = new blimp::TextureOptions(blimp::TextureOptions::WrapMode::MIRROR);
            options3 = new blimp::TextureOptions(blimp::TextureOptions::WrapMode::CLAMP_EDGE, blimp::TextureOptions::FilterMode::NEAREST);
            options4 = new blimp::TextureOptions(blimp::TextureOptions::FilterMode::NEAREST);
            options5 = new blimp::TextureOptions(
                0.5f,
                1.25f,
                blimp::TextureOptions::WrapMode::REPEAT,
                blimp::TextureOptions::WrapMode::MIRROR,
                blimp::TextureOptions::FilterMode::NEAREST,
                blimp::TextureOptions::FilterMode::LINEAR_MIPMAP_NEAREST
            );
            options6 = new blimp::TextureOptions(2.0f, 3.0f);
        }

        virtual void TearDown() {
            delete options;
            delete options2;
            delete options3;
            delete options4;
            delete options5;
            delete options6;
        }

        blimp::TextureOptions* options;
        blimp::TextureOptions* options2;
        blimp::TextureOptions* options3;
        blimp::TextureOptions* options4;
        blimp::TextureOptions* options5;
        blimp::TextureOptions* options6;
};

TEST_F(TextureOptionsTest, IsNotNull) {
    ASSERT_NE(options, nullptr);
    ASSERT_NE(options2, nullptr);
    ASSERT_NE(options3, nullptr);
    ASSERT_NE(options4, nullptr);
    ASSERT_NE(options5, nullptr);
    ASSERT_NE(options6, nullptr);
}

TEST_F(TextureOptionsTest, OptionsCorrect) {
    ASSERT_EQ(options -> getScaleS(), 1.0f);
    ASSERT_EQ(options -> getScaleT(), 1.0f);
    ASSERT_EQ(options -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options -> getWrapModeT(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options -> getMinFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options2 -> getScaleS(), 1.0f);
    ASSERT_EQ(options2 -> getScaleT(), 1.0f);
    ASSERT_EQ(options2 -> getWrapModeS(), blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options2 -> getWrapModeT(), blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options2 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options2 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options3 -> getScaleS(), 1.0f);
    ASSERT_EQ(options3 -> getScaleT(), 1.0f);
    ASSERT_EQ(options3 -> getWrapModeS(), blimp::TextureOptions::WrapMode::CLAMP_EDGE);
    ASSERT_EQ(options3 -> getWrapModeT(), blimp::TextureOptions::WrapMode::CLAMP_EDGE);
    ASSERT_EQ(options3 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options3 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options4 -> getScaleS(), 1.0f);
    ASSERT_EQ(options4 -> getScaleT(), 1.0f);
    ASSERT_EQ(options4 -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options4 -> getWrapModeT(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options4 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options4 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options5 -> getScaleS(), 0.5f);
    ASSERT_EQ(options5 -> getScaleT(), 1.25f);
    ASSERT_EQ(options5 -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options5 -> getWrapModeT(), blimp::TextureOptions::WrapMode::MIRROR);
    ASSERT_EQ(options5 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::NEAREST);
    ASSERT_EQ(options5 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR_MIPMAP_NEAREST);
    ASSERT_EQ(options6 -> getScaleS(), 2.0f);
    ASSERT_EQ(options6 -> getScaleT(), 3.0f);
    ASSERT_EQ(options6 -> getWrapModeS(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options6 -> getWrapModeT(), blimp::TextureOptions::WrapMode::REPEAT);
    ASSERT_EQ(options6 -> getMinFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
    ASSERT_EQ(options6 -> getMagFilterMode(), blimp::TextureOptions::FilterMode::LINEAR);
}

//////////////////// Window ////////////////////

class WindowTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            // window = new blimp::Window("BlimpTest");
            texture = new blimp::Texture("demo/assets/textures/blimp.png");
            scene = new blimp::Node();
            cube = new blimp::Mesh(new blimp::Cuboid(1, 1, 1), new blimp::LambertMaterial());
            cube -> setTexture(texture);
            scene -> addChild(cube);
            aLight = new blimp::AmbientLight(blimp::Color(blimp::Color::AQUA), 0.6f);
            dLight = new blimp::DirectionalLight(blimp::Color(blimp::Color::AQUA), 0.6f);
            pLight = new blimp::PointLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f);
            sLight = new blimp::SpotLight(blimp::Color(blimp::Color::AQUA), 0.6f, 0.5f, 0.2f);
            scene -> addChild(aLight);
            scene -> addChild(dLight);
            scene -> addChild(pLight);
            scene -> addChild(sLight);
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
        blimp::Texture *texture;
        blimp::Mesh *cube;
        blimp::Node *scene;
        blimp::PerspectiveCamera *camera;
        blimp::AmbientLight* aLight;
        blimp::DirectionalLight* dLight;
        blimp::PointLight* pLight;
        blimp::SpotLight* sLight;
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