

ecs_entity_t prefab_noise_chunk;

ecs_entity_t spawn_prefab_noise_chunk(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_chunk)
    zox_prefab_name("prefab_noise_chunk")
    zox_add_tag(e, NoiseChunk)
    ecs_defer_end(world);
    prefab_noise_chunk = e;
    return e;
}

ecs_entity_t spawn_voxel_noise_chunk_mesh(ecs_world_t *world, ecs_entity_t prefab, float3 position, float scale) {
    ecs_entity_t e = spawn_chunk(world, prefab, position, scale);
    zox_name("noise_chunk")
    // zox_set(e, AnimateChunk, { (((rand() % 100) / 100.0f) * animating_chunk_speed) }); // 0.0 });
    return e;
}