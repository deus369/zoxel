#ifndef zox_mod_chunks3
#define zox_mod_chunks3
/**
 *  Zox Voxels
 *
 *      - core voxel code
 *      - octree node, goes down n levels
 *      - can be rendered as cubes and optimized triangles
 *
 * */

zox_component_entity(VoxLink)
#include "chunks/_.c"
#include "streaming/_.c"
#include "structures/_.c"
#include "animations/_.c"

void module_dispose_chunks3(ecs_world_t *world, void *ctx) {
    dispose_hook_spawned_block();
}

zox_begin_module(Chunks3)
    initialize_hook_spawned_block();
    zox_define_component_entity(VoxLink)
    zox_module_dispose(module_dispose_chunks3)
    define_components_chunks(world);
    define_systems_chunks(world);
    spawn_prefabs_chunks(world);
    zox_import_module(Streaming)
    zox_import_module(Structures)
    zox_import_module(VoxelsAnimations)
zox_end_module(Chunks3)

#endif