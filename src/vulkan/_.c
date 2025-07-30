#ifndef zoxel_vulkan
#define zoxel_vulkan

// #include "vulkan/vulkan.c"
#include "util/vulkan_check.c"
#ifdef zox_vulkan
    #include "util/vulkan_setup.c"
#endif

void dispose_vulkan(ecs_world_t *world) {
#ifdef zox_vulkan
    dispose_vulkan_globals();
#endif
}

byte initialize_vulkan(ecs_world_t *world) {
    // load shaders, vulkan load shader
    return EXIT_SUCCESS;
}

byte check_vulkan_suppport() {
    const byte vulkan_supported = is_vulkan_supported();
    if (vulkan_supported) {
        zox_log(" > vulkan is supported");
    } else {
        zox_log(" ! vulkan not supported\n");
    }
    return vulkan_supported;
}

#endif
