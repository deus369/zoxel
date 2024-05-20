#include "vox.c"
#include "block_vox.c"
ecs_entity_t prefab_vox;
ecs_entity_t prefab_block_vox;

void spawn_prefabs_voxes(ecs_world_t *world) {
    prefab_vox = spawn_prefab_vox(world, prefab_chunk);
    prefab_block_vox = spawn_prefab_block_vox(world, prefab_vox);
}
