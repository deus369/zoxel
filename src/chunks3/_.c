/**
 *  Zox Voxels
 *
 *      - core voxel code
 *      - octree node, goes down n levels
 *      - can be rendered as cubes and optimized triangles
 *
 * */
#ifndef zox_mod_chunks3
#define zox_mod_chunks3

// rename to grid3D?
zox_component_entity(VoxLink)
#include "chunks/_.c"
#include "streaming/_.c"
#include "structures/_.c"
#include "animations/_.c"

void module_dispose_chunks3(ecs_world_t *world, void *ctx) {
    dispose_hook_spawned_block();
}

zox_begin_module(Chunks3)
    zox_define_component_entity(VoxLink)
    zox_module_dispose(module_dispose_chunks3)
    define_components_chunks(world);
    define_systems_chunks(world);
    initialize_hook_spawned_block();
    add_hook_key_down(key_down_toggle_debug_chunks);
    spawn_prefabs_chunks(world);
    zox_import_module(Streaming)
    zox_import_module(Structures)
    zox_import_module(VoxelsAnimations)
zox_end_module(Chunks3)

#endif