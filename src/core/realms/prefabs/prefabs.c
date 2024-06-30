ecs_entity_t prefab_realm;
ecs_entity_t local_realm;
#include "realm.c"

void spawn_prefabs_realms(ecs_world_t *world) {
    prefab_realm = spawn_prefab_realm(world);
}
