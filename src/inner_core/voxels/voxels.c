#ifndef zoxel_voxels
#define zoxel_voxels
//! The voxels Module.

// Sub Modules
#include "core/voxels_core.c"
// util
#include "vox/util/vox_read_util.c"

void VoxelsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Voxels);
    ECS_IMPORT(world, VoxelsCore);

    vox_file chicken_vox;
    read_vox(resources_folder_name"voxes/monsters/chicken.vox", &chicken_vox);
}
#endif