#include "chunk.c"
#include "chunk_base.c"
ecs_entity_t prefab_chunk_base;
ecs_entity_t prefab_chunk;

void spawn_prefabs_chunks(ecs_world_t *world) {
    prefab_chunk_base = spawn_prefab_chunk_base(world);
    prefab_chunk = spawn_prefab_chunk(world, prefab_chunk_base);
}
