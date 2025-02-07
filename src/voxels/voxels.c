/**
 *  Zox Voxels
 *
 *      - core voxel code
 *      - octree node, goes down n levels
 *      - can be rendered as cubes and optimized triangles
 *
 * */
#ifndef zox_mod_voxels
#define zox_mod_voxels

zox_component_entity(VoxLink)
#include "blocks/blocks.c"
#include "chunks/chunks.c"
#include "streaming/streaming.c"
#include "structures/structures.c"
#include "animations/voxels_animations.c"

zox_begin_module(Voxels)
    zox_define_component_entity(VoxLink)
    zox_import_module(Blocks)
    zox_import_module(Chunks)
    zox_import_module(Streaming)
    zox_import_module(Structures)
    zox_import_module(VoxelsAnimations)
zoxel_end_module(Voxels)

#endif
