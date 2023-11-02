#ifndef zoxel_opengl
#define zoxel_opengl

#include "util/import_opengl.c"
// zoxel_settings
float3 opengl_clear_color = { 125 / 255.0f, 125 / 255.0f, 125 / 255.0f };
// zoxel_data
#include "data/GLuint2.c"
// zoxel_util
#include "util/error_util.c"
#include "util/primitive_square.c"
#include "util/primitive_mesh_util.c"
#include "util/shaders_util.c"
#include "util/opengl_util.c"
#include "util/compute_util.c"
// loads / disposes all shaders, move to higher level
#include "util/opengl_main_util.c"

void check_compute() {
    if (check_compute_shader_support() == EXIT_FAILURE) zoxel_log(" ! opengl compute is not supported\n");
}

unsigned char initialize_opengl(ecs_world_t *world) {
    #ifdef zoxel_debug_opengl
        zoxel_log(" > initializing opengl\n");
    #endif
    print_opengl();
    check_compute();
    if (opengl_load_shaders(world) == EXIT_FAILURE) {
        zoxel_log(" - failed to load all shaders\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

zox_begin_module(OpenGL)
zoxel_end_module(OpenGL)

#endif
