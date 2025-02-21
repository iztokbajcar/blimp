#include <gtest/gtest.h>
#include "../../src/cubemap.hpp"

class CubemapTest : public testing::Test {
    protected:
        virtual void SetUp() {
            px = new blimp::Texture2D("demo/assets/textures/skybox/px.png");
            nx = new blimp::Texture2D("demo/assets/textures/skybox/nx.png");
            py = new blimp::Texture2D("demo/assets/textures/skybox/py.png");
            ny = new blimp::Texture2D("demo/assets/textures/skybox/ny.png");
            pz = new blimp::Texture2D("demo/assets/textures/skybox/pz.png");
            nz = new blimp::Texture2D("demo/assets/textures/skybox/nz.png");
            cubemap = new blimp::Cubemap(px, nx, py, ny, pz, nz);
        }

        virtual void TearDown() {
            delete cubemap;
            delete px;
            delete nx;
            delete py;
            delete ny;
            delete pz;
            delete nz;
        }

        blimp::Cubemap *cubemap;
        blimp::Texture2D *px;
        blimp::Texture2D *nx;
        blimp::Texture2D *py;
        blimp::Texture2D *ny;
        blimp::Texture2D *pz;
        blimp::Texture2D *nz; 
};

TEST_F(CubemapTest, IsNotNull) {
    ASSERT_NE(cubemap, nullptr);
}

TEST_F(CubemapTest, PXNotNull) {
    blimp::Texture2D* px = cubemap -> getPX();
    ASSERT_NE(px, nullptr);
}

TEST_F(CubemapTest, NXNotNull) {
    blimp::Texture2D* nx = cubemap -> getNX();
    ASSERT_NE(nx, nullptr);
}

TEST_F(CubemapTest, PYNotNull) {
    blimp::Texture2D* py = cubemap -> getPY();
    ASSERT_NE(py, nullptr);
}

TEST_F(CubemapTest, NYNotNull) {
    blimp::Texture2D* ny = cubemap -> getNY();
    ASSERT_NE(ny, nullptr);
}

TEST_F(CubemapTest, PZNotNull) {
    blimp::Texture2D* pz = cubemap -> getPZ();
    ASSERT_NE(pz, nullptr);
}

TEST_F(CubemapTest, NZNotNull) {
    blimp::Texture2D* nz = cubemap -> getNZ();
    ASSERT_NE(nz, nullptr);
}
