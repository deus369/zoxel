#include "block_vox_meta.c"
#include "vox.c"
#include "block_vox.c"
#include "vox_file.c"
#include "vox_generated.c"
#include "vox_texture.c"
ecs_entity_t prefab_block_vox_meta;
ecs_entity_t prefab_vox;
ecs_entity_t prefab_block_vox;
ecs_entity_t prefab_vox_file;
ecs_entity_t prefab_vox_generated;
ecs_entity_t prefab_vox_texture;

void spawn_prefabs_voxes(ecs_world_t *world) {
    prefab_block_vox_meta = spawn_prefab_block_box_meta(world, prefab_block);
    prefab_vox = spawn_prefab_vox(world, prefab_chunk_octree);
    prefab_block_vox = spawn_prefab_block_vox(world, prefab_vox);
    prefab_vox_file = spawn_prefab_vox_file(world);
    prefab_vox_generated = spawn_prefab_vox_generated(world, prefab_vox);
    prefab_vox_texture = spawn_prefab_vox_texture(world, prefab_texture);
}
