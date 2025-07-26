#include "cube.c"
#include "cube_textured.c"
ecs_entity_t prefab_cube;
ecs_entity_t prefab_cube_textured;

void spawn_prefabs_cubes(ecs_world_t *world) {
    prefab_cube = spawn_prefab_cube(world);
    prefab_cube_textured = spawn_prefab_cube_textured(world, prefab_cube);
}
