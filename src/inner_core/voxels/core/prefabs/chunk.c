//! Basic noise texture.
ecs_entity_t chunk_prefab;

void add_chunk(ecs_world_t *world, ecs_entity_t prefab, int3 size)
{
    zoxel_add(world, prefab, Chunk);
    zoxel_set(world, prefab, ChunkSize, { size });
    zoxel_set(world, prefab, ChunkDirty, { 0 });
    zoxel_set(world, prefab, ChunkPosition, { { 0, 0, 0 } });
}

void add_generate_chunk(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_set(world, e, EntityDirty, { 0 });
    zoxel_set(world, e, GenerateChunk, { 1 });
}

void add_noise_chunk(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, NoiseChunk);
    zoxel_set(world, e, EntityDirty, { 0 });
    zoxel_set(world, e, GenerateChunk, { 1 });
    // zoxel_set(world, e, AnimateTexture, { 0.0 });
}

ecs_entity_t spawn_chunk_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    const int3 size = { 16, 16, 16 };
    ecs_entity_t e = ecs_new_prefab(world, "chunk_prefab");
    add_seed(world, e, 666);
    add_chunk(world, e, size);
    add_noise_chunk(world, e);
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab chunk_prefab [%lu].\n", (long int) (e));
    #endif
    chunk_prefab = e;
    return e;
}

//! Spawn a Chunk.
ecs_entity_t spawn_chunk(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, chunk_prefab);
    zoxel_add_tag(world, e, NoiseChunk);
    zoxel_log("Spawned Texture [%lu]\n", (long unsigned int) e);
    ecs_defer_end(world);
    return e;
}