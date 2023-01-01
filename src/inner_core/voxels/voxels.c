#ifndef zoxel_voxels
#define zoxel_voxels

// Sub Modules
#include "core/voxels_core.c"
// util
#include "vox/vox.c"

//! The voxels Module.
void VoxelsImport(ecs_world_t *world)
{
    zoxel_define_module(Voxels)
    ECS_IMPORT(world, VoxelsCore);
    ECS_IMPORT(world, Vox);
}
#endif