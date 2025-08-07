#ifndef zoxm_chunks3
#define zoxm_chunks3
/**
 *  Zox Voxels
 *
 *      - core voxel code
 *      - octree node, goes down n levels
 *      - can be rendered as cubes and optimized triangles
 *
 * */

#define zoxp_read_voxels EcsOnLoad
#define zoxp_write_voxels EcsOnStore

zox_component_entity(VoxLink)
#include "chunks/_.c"
#include "streaming/_.c"
#include "structures/_.c"
#include "animations/_.c"
#include "vodes3/_.c"
#include "vrays/_.c"

void module_dispose_chunks3(ecs_world_t *world, void *ctx) {
    dispose_hook_on_destroyed_VoxelNode();
}

zox_begin_module(Chunks3)
    zox_define_component_entity(VoxLink)
    define_components_chunks(world);
    define_systems_chunks(world);
    spawn_prefabs_chunks(world);
    zox_import_module(Streaming)
    zox_import_module(Structures)
    zox_import_module(VoxelsAnimations)
    zox_import_module(Vodes3)
    zox_import_module(Vrays)
    zox_module_dispose(module_dispose_chunks3);
    initialize_hook_on_destroyed_VoxelNode();
    add_hook_on_destroyed_VoxelNode(destroy_node_link_VoxelNode);
zox_end_module(Chunks3)

#endif