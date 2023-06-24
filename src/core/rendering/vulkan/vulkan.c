#ifndef zoxel_vulkan
#define zoxel_vulkan

// todo: a simple triangle mesh / entity with opengl
// todo: next, render a simple triangle with vulkan instead of opengl
//      - use a --vulkan option when running zoxel
// todo: load ui shaders with vulkan
// todo: update vulkan shader meshes in threaded systems

unsigned char initialize_vulkan(ecs_world_t *world) {
    // load shaders, vulkan load shader
    return EXIT_SUCCESS;
}

zox_begin_module(Vulkan)
zoxel_end_module(Vulkan)

#endif