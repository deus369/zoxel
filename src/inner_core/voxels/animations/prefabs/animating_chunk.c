ecs_entity_t prefab_animating_chunk;

ecs_entity_t spawn_prefab_animating_chunk(ecs_world_t *world) {
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_noise_chunk);
    ecs_add_id(world, e, EcsPrefab);
    add_chunk_colors(world, e);
    zox_prefab_set(e, ChunkSize, {{ 16, 16, 16 }})
    zox_prefab_set(e, AnimateChunk, { 1.0 })
    zox_prefab_set(e, ChunkDirty, { 0 })
    zox_prefab_set(e, MeshDirty, { 0 })
    add_gpu_colors(world, e);
    // testing: set colors
    ColorRGBs *colorRGBs = ecs_get_mut(world, e, ColorRGBs);
    resize_memory_component(ColorRGBs, colorRGBs, color_rgb, 8)
    for (int i = 0; i < 8; i++)
        colorRGBs->value[i] = (color_rgb) {155 - (rand() % 60), 225 - (rand() % 60), 255 - (rand() % 60) };
    zox_modified(e, ColorRGBs)
    prefab_animating_chunk = e;
#ifdef zoxel_debug_prefabs
    zox_log("spawn_prefab animating_chunk [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_animating_chunk(ecs_world_t *world, float3 position, float scale, unsigned char division) {
    ecs_entity_t e = spawn_chunk(world, prefab_animating_chunk, position, scale);
    zox_set(e, AnimateChunk, { (((rand() % 100) / 100.0f) * animating_chunk_speed) })
    zox_set(e, RenderLod, { division })
    spawn_gpu_colors(world, e);
    // zox_log(" > spawned animating_chunk at [%fx%fx%f]\n", position.x, position.y, position.z)
    return e;
}

void test_animating_chunks(ecs_world_t *world, float3 position) {
    const float spawn_scale = 1.0f;
    // const float spawnRange = 0.5f;
    spawn_animating_chunk(world, (float3) { position.x - 3, position.y, position.z + 1 }, spawn_scale, 0);
    spawn_animating_chunk(world, (float3) { position.x - 1.5f, position.y, position.z + 1 }, spawn_scale, 1);
    spawn_animating_chunk(world, (float3) { position.x, position.y, position.z + 1 }, spawn_scale, 2);
    spawn_animating_chunk(world, (float3) { position.x + 1.5f, position.y, position.z + 1 }, spawn_scale, 3);
    spawn_animating_chunk(world, (float3) { position.x + 3, position.y, position.z + 1 }, spawn_scale, 4);
}
