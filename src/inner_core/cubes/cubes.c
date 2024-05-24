#ifndef zox_cubes
#define zox_cubes

const int custom_mesh_spawn_count = 64;
const float2 spawnBounds = { 2.2f, 1.2f };
#include "prefabs/cube.c"
#include "prefabs/cube_textured.c"

void spawn_prefabs_cubes(ecs_world_t *world) {
    spawn_prefab_cube(world);
    spawn_prefab_cube_textured(world);
    #ifdef zoxel_test_cubes
    for (int i = 0; i < custom_mesh_spawn_count; i++) {
        spawn_cube(world, prefab_cube, (float3) {
            -spawnBounds.x + (rand() % 100) * 0.02f * spawnBounds.x,
            -spawnBounds.y + (rand() % 100) * 0.02f * spawnBounds.y, 0 });
    }
    #endif
    #ifdef zoxel_test_cubes_textured
    spawn_cube_textured(world, (float3) { 0, 0, 0 });
    // for (int i = 0; i < custom_mesh_spawn_count; i++) {
    //     spawn_cube_textured(world, (float3) {
    //         -spawnBounds.x + (rand() % 100) * 0.02f * spawnBounds.x,
    //         -spawnBounds.y + (rand() % 100) * 0.02f * spawnBounds.y, 0 });
    // }
    #endif
}

zox_begin_module(Cubes)
spawn_prefabs_cubes(world);
zoxel_end_module(Cubes)

#endif
