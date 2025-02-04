#include "block.c"
ecs_entity_t prefab_block;

void spawn_prefabs_blocks(ecs_world_t *world) {
    prefab_block = spawn_prefab_block(world);
}
