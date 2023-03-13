#ifndef zoxel_opengl
#define zoxel_opengl

#include "dynamic/opengl_functions.c"
// util
#include "util/error_util.c"
#include "util/primitive_square.c"
#include "util/primitive_mesh_util.c"
#include "util/shaders_util.c"    // uses initialize_mesh
#include "util/opengl_util.c"
#include "util/compute_util.c"
// render2D
#include "render2D/material2D.c"
#include "render2D/instanced2D_material.c"
// render2D textured
#include "render2D_textured/material2D_textured.c"
#include "render2D_textured/shader2D_textured.c"
// render3D
#include "data/material3D.c"
#include "rendering/instanced3D_material.c"
// render3D textured
#include "data/material3D_textured.c"
#include "rendering/unique3D_material.c"
#include "rendering/shader3D_textured.c"
// material3D_colored
#include "data/material3D_colored.c"
#include "rendering/shader3D_colored.c"
#include "util/opengl_main_util.c"

void OpenGLImport(ecs_world_t *world)
{
    zoxel_module(OpenGL)
    opengl_load_functions();
    if (load_all_shaders() == EXIT_FAILURE) {
        zoxel_log("Failed to InitializeOpenGL.\n");
        return;
    }
    print_opengl();
    if (check_compute_shader_support() == EXIT_FAILURE) {
        zoxel_log("Failed to support Compute Shaders.\n");
        return;
    }
    if (test_compute_shader() == EXIT_FAILURE) {
        zoxel_log("Failed to creating compute shader.\n");
        return;
    }
}
#endif