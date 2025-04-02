#ifndef zoxel_opengl
#define zoxel_opengl

#include "_include.c"
#include "data/GLuint2.c"
#include "util/util.c"

void check_compute() {
    if (check_compute_shader_support() == EXIT_FAILURE) zox_log(" ! opengl compute is not supported\n");
}

byte initialize_opengl(ecs_world_t *world) {
#ifdef zoxel_on_windows
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "GLEW initialization failed: %s\n", glewGetErrorString(err));
        return 1;
    }
#endif
#ifdef zoxel_debug_opengl
    zox_log(" > initializing opengl\n")
#endif
    // if (!has_opengl_extensions()) return EXIT_FAILURE;
    print_opengl();
    check_frame_buffer();
    // check_compute();
    // check_geometry();
    return EXIT_SUCCESS;
}

zox_begin_module(OpenGL)
    add_to_update_loop(opengl_clear_viewport_all);
zox_end_module(OpenGL)

#endif
