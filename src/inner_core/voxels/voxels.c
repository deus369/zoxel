#ifndef zoxel_voxels
#define zoxel_voxels

#include "core/core.c"
#include "terrain/terrain.c"
#include "vox/vox.c"

//! The voxels Module.
void VoxelsImport(ecs_world_t *world)
{
    zoxel_module(Voxels)
    zoxel_import_module(VoxelsCore)
    zoxel_import_module(Vox)
    zoxel_import_module(Terrain)
}
#endif