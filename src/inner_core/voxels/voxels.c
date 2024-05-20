#ifndef zox_voxels
#define zox_voxels

#include "blocks/blocks.c"
#include "chunks/chunks.c"
#include "structures/structures.c"
#include "animations/voxels_animations.c"
#include "voxes/voxes.c"
#include "terrain/terrain.c"

void spawn_prefabs_voxels(ecs_world_t *world) {
    spawn_prefabs_blocks(world);
    spawn_prefabs_chunks(world);
    spawn_prefabs_voxels_structures(world);
    spawn_prefabs_voxel_animations(world);
    spawn_prefabs_voxes(world);
    spawn_prefabs_terrain(world);
}

zox_begin_module(Voxels)
zox_import_module(Blocks)
zox_import_module(Chunks)
zox_import_module(Structures)
zox_import_module(VoxelsAnimations)
zox_import_module(Voxes)
zox_import_module(Terrain)
zoxel_end_module(Voxels)

#endif
