

ecs_entity_t prefab_noise_chunk;

ecs_entity_t spawn_prefab_noise_chunk(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_noise_chunk");
    ecs_add(world, e, NoiseChunk);
    ecs_add(world, e, AnimateChunk);
    ecs_defer_end(world);
    prefab_noise_chunk = e;
    return e;
}


ecs_entity_t spawn_voxel_noise_chunk_mesh(ecs_world_t *world, ecs_entity_t prefab, float3 position, float scale)
{
    ecs_entity_t e = spawn_voxel_chunk_mesh(world, prefab, position, scale);
    zoxel_set(world, e, AnimateChunk, { (((rand() % 100) / 100.0f) * noiseChunkAnimateSpeed) }); // 0.0 });
    return e;
}