#include "chunk.c"
ecs_entity_t prefab_chunk;

void spawn_prefabs_chunks(ecs_world_t *world) {
    set_max_octree_length(max_octree_depth);
    // prefab_chunk = spawn_prefab_chunk(world);
    prefab_chunk = spawn_prefab_chunk(world);
    // prefab_chunk_noise = spawn_prefab_chunk_noise(world, prefab_chunk);
}
