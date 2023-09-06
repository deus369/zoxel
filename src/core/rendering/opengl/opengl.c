#ifndef zoxel_opengl
#define zoxel_opengl

#define GL_GLEXT_PROTOTYPES
#ifdef USE_SDL_3
    #include <SDL3/SDL_opengl.h>
#else
    #ifdef zoxel_on_android
        #include <SDL_opengl.h>
    #else
        #include <SDL2/SDL_opengl.h>
    #endif
#endif
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
// basics 2D
#include "shaders/instanced2D.c"
#include "shaders/textured2D.c"
#include "render2D/material2D.c"
#include "render2D/instanced2D_material.c"
#include "render2D_textured/textured2D_material.c"
#include "render2D_textured/shader_textured2D.c"
// loads / disposes all shaders, move to higher level
#include "util/opengl_main_util.c"

unsigned char initialize_opengl(ecs_world_t *world) {
    #ifdef zoxel_debug_opengl
        zoxel_log(" > initializing opengl\n");
    #endif
    /*glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "   ! error initializing GLEW: %s\n", glewGetErrorString(err));
        exit(1);
    }*/
    print_opengl();
    if (check_compute_shader_support() == EXIT_FAILURE) zoxel_log(" ! compute is not supported\n");
    if (opengl_load_shaders(world) == EXIT_FAILURE) {
        zoxel_log(" - failed to load all shaders\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

zox_begin_module(OpenGL)
zoxel_end_module(OpenGL)

#endif