ecs_entity_t prefab_pickup;
ecs_entity_t prefab_pickup_basic;
#include "pickup.c"

void spawn_prefabs_pickups(ecs_world_t *world) {
    prefab_pickup_basic = spawn_prefab_pickup(world, prefab_cube);
#ifdef zox_prefabs_non_textured
    prefab_pickup = spawn_prefab_pickup(world, prefab_cube);
#else
    prefab_pickup = spawn_prefab_pickup(world, prefab_cube_textured);
#endif
}
