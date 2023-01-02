#ifndef zoxel_voxels
#define zoxel_voxels

// Sub Modules
#include "core/voxels_core.c"
// util
#include "vox/vox.c"

//! The voxels Module.
void VoxelsImport(ecs_world_t *world)
{
    zoxel_module(Voxels)
    zoxel_import_module(VoxelsCore)
    zoxel_import_module(Vox)
}
#endif