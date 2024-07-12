#include "pickup.c"
ecs_entity_t prefab_pickup;

void spawn_prefabs_pickups(ecs_world_t *world) {
    prefab_pickup = spawn_prefab_pickup(world, prefab_cube);
}
