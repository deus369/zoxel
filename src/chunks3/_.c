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
#include "vodes3/_.c"

zox_begin_module(Chunks3)
    zox_define_component_entity(VoxLink)
    define_components_chunks(world);
    define_systems_chunks(world);
    spawn_prefabs_chunks(world);
    zox_import_module(Streaming)
    zox_import_module(Structures)
    zox_import_module(VoxelsAnimations)
    zox_import_module(Vodes3)
zox_end_module(Chunks3)

#endif