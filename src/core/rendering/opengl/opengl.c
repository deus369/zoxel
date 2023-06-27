#ifndef zoxel_opengl
#define zoxel_opengl

// zoxel_settings
// float3 opengl_clear_color = { 2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f };
float3 opengl_clear_color = { 125 / 255.0f, 125 / 255.0f, 125 / 255.0f };
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

unsigned char initialize_opengl(ecs_world_t *world) {
    if (opengl_load_functions() == EXIT_FAILURE) {
        zoxel_log(" - opengl failed to load [opengl_load_functions]\n");
        return EXIT_FAILURE;
    }
    print_opengl();
    if (check_compute_shader_support() == EXIT_FAILURE) zoxel_log(" ! compute is not supported\n");
    if (opengl_load_shaders() == EXIT_FAILURE) {
        zoxel_log(" - failed to load all shaders\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

zox_begin_module(OpenGL)
zoxel_end_module(OpenGL)

#endif