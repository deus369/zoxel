#include "pickup.c"
ecs_entity_t prefab_pickup;

void spawn_prefabs_pickups(ecs_world_t *world) {
#ifdef zox_prefabs_non_textured
    prefab_pickup = spawn_prefab_pickup(world, prefab_cube);
#else
    prefab_pickup = spawn_prefab_pickup(world, prefab_cube_textured);
#endif
}
