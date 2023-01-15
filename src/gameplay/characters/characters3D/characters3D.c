#ifndef zoxel_characters3D
#define zoxel_characters3D

const int spawn_characters3D_count = 64;
zoxel_declare_tag(Character3D)
zoxel_component(Character3DLink, ecs_entity_t)
#include "prefabs/character3D.c"
#include "util/character3D.c"

//! Testing, spawn more!
void spawn_many_characters3D(ecs_world_t *world)
{
    vox_file vox_slime;
    if (!read_vox(resources_folder_name"voxes/monsters/slime.vox", &vox_slime) == 0)
    {
        zoxel_log("Cannot find slime.vox!");
        return;
    }
    zoxel_log("spawn_many_characters3D [%i]\n", spawn_characters3D_count);
    const float model_scale = 0.015f;
    float cameraY = 1.02f * overall_voxel_scale; // ecs_get(world, main_cameras[0], Position)->value.y; //  100.0f;
    float radius = 0.5f * overall_voxel_scale; // 16.0f;
    for (int i = 0; i < spawn_characters3D_count; i++)
    {
        spawn_character3D(world, character3D_prefab, &vox_slime, (float3) {
            - radius + (rand() % 100) / 101.0f * radius * 2.0f,
            cameraY, // 100.0f,
            - radius + (rand() % 100) / 101.0f * radius * 2.0f }, model_scale);
    }
    dispose_vox_file(&vox_slime); //! Free vox files after use
}

//! A module for 3 dimensional characters.
void Characters3DImport(ecs_world_t *world)
{
    zoxel_module(Characters3D)
    zoxel_define_tag(Character3D)
    zoxel_define_component(Character3DLink)
    spawn_prefab_character3D(world);
    #ifdef zoxel_test_character3Ds
    spawn_many_characters3D(world);
    #endif
}
#endif