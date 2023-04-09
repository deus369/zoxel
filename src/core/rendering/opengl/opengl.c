#ifndef zoxel_opengl
#define zoxel_opengl

#include "dynamic/opengl_functions.c"
#include "util/error_util.c"
#include "util/primitive_square.c"
#include "util/primitive_mesh_util.c"
#include "util/shaders_util.c"
#include "util/opengl_util.c"
#include "util/compute_util.c"
// shaders
#include "shaders/colored3D.c"
#include "shaders/instanced2D.c"
#include "shaders/instanced3D.c"
#include "shaders/textured2D.c"
#include "shaders/textured3D.c"
// render2D
#include "render2D/material2D.c"
#include "render2D/instanced2D_material.c"
#include "render2D_textured/material2D_textured.c"
#include "render2D_textured/shader2D_textured.c"
// render3D
#include "data/material3D.c"
#include "rendering/instanced3D_material.c"
#include "data/material3D_textured.c"
#include "rendering/unique3D_material.c"
#include "rendering/shader3D_textured.c"
#include "data/material3D_colored.c"
#include "rendering/shader3D_colored.c"
#include "util/opengl_main_util.c"

zoxel_begin_module(OpenGL)
opengl_load_functions();
print_opengl();
if (check_compute_shader_support() == EXIT_FAILURE) {
    zoxel_log(" - compute is not supported\n");
}
if (load_all_shaders() == EXIT_FAILURE) {
    zoxel_log(" - failed to load all shaders\n");
    return;
}
zoxel_end_module(OpenGL)

/*if (test_compute_shader() == EXIT_FAILURE) {
    zoxel_log(" - failed to create compute shader\n");
    return;
}*/

#endif