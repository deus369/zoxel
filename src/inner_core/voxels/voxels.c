#ifndef Zoxel_Voxels
#define Zoxel_Voxels
//! The voxels Module.

// Sub Modules
#include "core/voxels_core.h"

void VoxelsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Voxels);
    ECS_IMPORT(world, VoxelsCore);
}
#endif