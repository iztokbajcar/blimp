#include <gtest/gtest.h>
#include "test_ambientlight.hpp"
#include "test_color.hpp"
#include "test_cubemap.hpp"
#include "test_cuboid.hpp"
#include "test_directionallight.hpp"
#include "test_geometry.hpp"
#include "test_light.hpp"
#include "test_material.hpp"
#include "test_mesh.hpp"
#include "test_node.hpp"
#include "test_normalmaterial.hpp"
#include "test_orthographiccamera.hpp"
#include "test_perspectivecamera.hpp"
#include "test_phongmaterial.hpp"
#include "test_pointlight.hpp"
#include "test_regularpolygon.hpp"
#include "test_regularprism.hpp"
#include "test_regularpyramid.hpp"
#include "test_shader.hpp"
#include "test_spotlight.hpp"
#include "test_sprite.hpp"
#include "test_spritematerial.hpp"
#include "test_texturable.hpp"
#include "test_texture2d.hpp"
#include "test_textureoptions.hpp"
#include "test_window.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}