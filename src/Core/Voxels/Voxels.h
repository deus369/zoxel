#ifndef Zoxel_Voxels
#define Zoxel_Voxels
//! The Voxels Module.

// Sub Modules
#include "Core/VoxelsCore.h"

void VoxelsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Voxels);
    InitializeVoxelsCore(world);
}

#endif