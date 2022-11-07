//! Basic noise texture.
ecs_entity_t chunk_prefab;

void add_chunk(ecs_world_t *world, ecs_entity_t prefab, int3 size)
{
    zoxel_add_component(world, prefab, Chunk);
    zoxel_set_component(world, prefab, ChunkSize, { size });
}

void add_noise_chunk(ecs_world_t *world, ecs_entity_t e)
{
    zoxel_add_tag(world, e, NoiseChunk);
    zoxel_set_component(world, e, EntityDirty, { 0 });
    zoxel_set_component(world, e, GenerateChunk, { 1 });
    // zoxel_set_component(world, e, AnimateTexture, { 0.0 });
}

void spawn_chunk_prefab(ecs_world_t *world)
{
    const int3 size = { 16, 16, 16 };
    ecs_entity_t e = ecs_new_prefab(world, "chunk_prefab");
    add_seed(world, e, 666);
    add_chunk(world, e, size);
    add_noise_chunk(world, e);
    chunk_prefab = e;
}

//! Spawn a Chunk.
ecs_entity_t spawn_chunk(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, chunk_prefab);
    printf("Spawned Texture [%lu]\n", (long unsigned int) e);
    return e;
}