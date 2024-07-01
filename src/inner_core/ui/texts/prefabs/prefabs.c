#include "zext.c"
ecs_entity_t prefab_zext;

void spawn_prefabs_texts(ecs_world_t *world) {
    prefab_zext = spawn_prefab_zext(world);
}
