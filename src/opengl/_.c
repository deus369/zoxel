// OpenGL Wrapper for Zoxel
#ifndef zoxel_opengl
#define zoxel_opengl

// byte shader_include_es = 1;
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>
int zox_max_ubo_size = 256;
#include "data/_.c"
#include "util/_.c"

byte initialize_opengl(ecs_world_t *world) {
#ifdef zoxel_on_windows
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf(stderr, "[glewInit] failed - [%s]\n", glewGetErrorString(err));
        return EXIT_FAILURE;
    }
#endif
    check_frame_buffer();
    check_compute();
    // check_geometry();
    if (is_log_sdl) {
        zox_log_sdl("zoxel opengl version [%u]", shader_opengl_version)
        print_opengl();
    }
    zox_max_ubo_size = zox_get_safe_ubo_size();
    zox_log("+++ max ubo: %i +++", zox_get_max_ubo_size(), zox_max_ubo_size);
    return EXIT_SUCCESS;
}

#endif