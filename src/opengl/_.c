// OpenGL Wrapper for Zoxel
#ifndef zoxel_opengl
#define zoxel_opengl

unsigned short shader_opengl_version = 300;
byte shader_include_es = 1;
#define GL_GLEXT_PROTOTYPES
    #ifdef zox_lib_sdl_direct
        #include <SDL_opengl.h>
    #else
    #ifdef USE_SDL_3
        #include <SDL3/SDL_opengl.h>
    #else
        #include <SDL2/SDL_opengl.h>
    #endif
#endif
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
    /*if (!has_opengl_extensions()) {
        zox_log_error("opengl does not have required extensions")
        // return EXIT_FAILURE;
    }*/
    check_frame_buffer();
    check_compute();
    // check_geometry();
    if (is_log_sdl) {
        zox_log_sdl("zoxel opengl version [%u] is es [%i]", shader_opengl_version, shader_include_es)
        print_opengl();
    }
    return EXIT_SUCCESS;
}

#endif