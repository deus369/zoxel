#ifndef zoxel_tiles
#define zoxel_tiles
//! The voxels Module.

// Sub Modules
//#include "core/voxels_core.h"

void TilesImport(ecs_world_t *world)
{
    ECS_MODULE(world, Tiles);
    // ECS_IMPORT(world, VoxelsCore);
}
#endif