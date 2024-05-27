#include "vox.c"
#include "block_vox.c"
#include "vox_file.c"
#include "vox_generated.c"
ecs_entity_t prefab_vox;
ecs_entity_t prefab_block_vox;
ecs_entity_t prefab_vox_file;
ecs_entity_t prefab_vox_generated;

void spawn_prefabs_voxes(ecs_world_t *world) {
    prefab_vox = spawn_prefab_vox(world, prefab_chunk);
    prefab_block_vox = spawn_prefab_block_vox(world, prefab_vox);
    prefab_vox_file = spawn_prefab_vox_file(world);
    prefab_vox_generated = spawn_prefab_vox_generated(world, prefab_vox);
}
