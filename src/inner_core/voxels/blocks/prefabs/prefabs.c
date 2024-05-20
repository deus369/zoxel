#include "block.c"
ecs_entity_t prefab_voxel;

void spawn_prefabs_blocks(ecs_world_t *world) {
    prefab_voxel = spawn_prefab_voxel(world);
}
