#ifndef zoxel_voxels_vox
#define zoxel_voxels_vox

// #define zoxel_debug_vox_read

// tags
ECS_DECLARE(Vox);
// util
#include "util/vox_read_util.c"
// prefabs
#include "prefabs/vox.c"
// systems
// #include "systems/noise_chunk_system.c"

//! The voxels core Sub Module.
void VoxImport(ecs_world_t *world)
{
    ECS_MODULE(world, Vox);
    ECS_TAG_DEFINE(world, Vox);
    spawn_prefab_vox(world);
    #ifdef zoxel_test_voxels_terrain
        vox_file chicken_vox;
        if (read_vox(resources_folder_name"voxes/monsters/chicken.vox", &chicken_vox) == 0)
        {
            //! Use vox files to spawn a vox entity!
            // spawn_vox_from_vox_file(chicken_vox);
            float4 rotation = quaternion_from_euler((float3) { 0, 180 * degreesToRadians, 0 });  // (float4) { 0, -1.6f, 0, -1.0f }
            float3 spawn_position = (float3) { 0, 0, -1.6f };
            #ifdef zoxel_test_voxels_terrain
                spawn_position.y += 2.6f;
            #endif
            spawn_vox_from_file(world, &chicken_vox, (float3) { 0.6f, spawn_position.y, spawn_position.z }, rotation, 0.15f);
            spawn_vox_from_file(world, &chicken_vox, (float3) { -0.6f, spawn_position.y, spawn_position.z }, rotation, 0.15f);
            //! Free vox files after use
            dispose_vox_file(&chicken_vox);
        }
    #endif
}
#endif