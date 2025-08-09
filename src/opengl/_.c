// OpenGL Wrapper for Zoxel
#ifndef zoxel_opengl
#define zoxel_opengl

// byte shader_include_es = 1;
#include "data/_.c"
#include "util/_.c"

byte zox_init_glew() {
#ifdef zox_windows
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        zox_log_errno("[glewInit] failed - [%s]", glewGetErrorString(err));
        return EXIT_FAILURE;
    }
#endif
    return EXIT_SUCCESS;
}

void initialize_opengl() {
    check_frame_buffer();
    check_compute();
    // check_geometry();
    if (is_log_sdl) {
        zox_log_sdl("zoxel opengl version [%u]", shader_opengl_version)
        print_opengl();
    }
    zox_logi("UBO Size [%i]", zox_get_safe_ubo_size());
}

#endif