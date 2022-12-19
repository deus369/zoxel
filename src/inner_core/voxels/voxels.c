#ifndef zoxel_voxels
#define zoxel_voxels

// #define zoxel_debug_vox_read

// Sub Modules
#include "core/voxels_core.c"
// util
#include "vox/util/vox_read_util.c"

//! The voxels Module.
void VoxelsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Voxels);
    ECS_IMPORT(world, VoxelsCore);
    vox_file chicken_vox;
    if (read_vox(resources_folder_name"voxes/monsters/chicken.vox", &chicken_vox) == 0)
    {
        //! Use vox files to spawn a vox entity!
        // spawn_vox_from_vox_file(chicken_vox);
        //! Free vox files after use
        dispose_vox_file(&chicken_vox);
    }
}
#endif