#include "texture_vox.c"
#include "block_vox_meta.c"
#include "vox.c"
#include "vox_instanced.c"
#include "vox_file.c"
#include "vox_generated.c"
#include "block_vox.c"
#include "block_vox_instanced.c"

ecs_entity_t prefab_vox_texture;
ecs_entity_t prefab_block_vox_meta;
ecs_entity_t prefab_vox;
ecs_entity_t prefab_vox_instanced;
ecs_entity_t prefab_vox_generated;
ecs_entity_t prefab_vox_file;
ecs_entity_t prefab_block_vox;
ecs_entity_t prefab_block_vox_instanced;

void zox_define_prefabs_voxes(ecs_world_t *world) {
    prefab_vox_texture = spawn_prefab_vox_texture(world, prefab_texture);
    prefab_block_vox_meta = spawn_prefab_block_vox_meta(world, prefab_block, prefab_block_vox);
    prefab_vox = spawn_prefab_vox(world, prefab_chunk);
    prefab_vox_instanced = spawn_prefab_vox_instanced(world, prefab_renderer_instance);
    prefab_vox_file = spawn_prefab_vox_file(world, prefab_chunk_base);
    zox_add_tag(prefab_vox_file, VoxMesh)
    prefab_vox_generated = spawn_prefab_vox_generated(world, prefab_vox);
    zox_add_tag(prefab_vox_generated, VoxMesh)
    // block voxes
    prefab_block_vox = spawn_prefab_block_vox(world, prefab_vox);
    zox_add_tag(prefab_block_vox, VoxMesh)
    prefab_block_vox_instanced = spawn_prefab_block_vox_instanced(world, prefab_vox_instanced);
}