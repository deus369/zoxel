/*ecs_entity_t spawn_prefab_chunk_noise(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_chunk_noise")
    zox_add_tag(e, NoiseChunk)
    return e;
}

ecs_entity_t spawn_chunk_noise(ecs_world_t *world, const ecs_entity_t prefab, const float3 position, const float scale) {
    const ecs_entity_t e = spawn_chunk(world, prefab, position);
    zox_name("chunk_noise")
    zox_set(e, Scale1D, { scale })
    // zox_set(e, AnimateChunk, { (((rand() % 100) / 100.0f) * animating_chunk_speed) });
    return e;
}
*/
