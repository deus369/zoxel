#ifndef zoxel_vulkan
#define zoxel_vulkan

// todo: a simple triangle mesh / entity with opengl
// todo: next, render a simple triangle with vulkan instead of opengl
//      - use a --vulkan option when running zoxel
// todo: load ui shaders with vulkan
// todo: update vulkan shader meshes in threaded systems

// #include "vulkan/vulkan.c"
#include "util/vulkan_check.c"
#ifdef zox_include_vulkan
    #include "util/vulkan_setup.c"
#endif

void dispose_resources_vulkan(ecs_world_t *world) {
#ifdef zox_include_vulkan
    dispose_vulkan();
#endif
}

unsigned char initialize_vulkan(ecs_world_t *world) {
    // load shaders, vulkan load shader
    return EXIT_SUCCESS;
}

void check_vulkan_suppport() {
    if (is_vulkan_supported()) zox_logg(" > vulkan is supported\n")
    else zox_logg(" ! vulkan not supported\n")
}

zox_begin_module(Vulkan)
zoxel_end_module(Vulkan)

#endif
