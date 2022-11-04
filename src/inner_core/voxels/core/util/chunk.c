
//! Spawn a Chunk.
ecs_entity_t spawn_chunk(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, chunk_prefab);
    printf("Spawned Texture [%lu]\n", (long unsigned int) e);
    return e;
}