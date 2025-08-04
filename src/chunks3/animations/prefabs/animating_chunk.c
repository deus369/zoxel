ecs_entity_t spawn_prefab_animating_chunk(ecs_world_t *world, const ecs_entity_t prefab) {
    const int3 chunk_size = (int3) { 16, 16, 16 };
    zox_instance(prefab)
    ecs_add_id(world, e, EcsPrefab);
    prefab_add_chunk_colors(world, e);
    zox_prefab_set(e, ChunkSize, { chunk_size })
    zox_prefab_set(e, AnimateChunk, { 1.0 })
    zox_prefab_set(e, ChunkDirty, { chunk_dirty_state_none })
    zox_prefab_set(e, ChunkMeshDirty, { chunk_dirty_state_none })
    zox_prefab_set(e, MeshDirty, { 0 })
    add_gpu_colors(world, e);
    // testing: set colors
    zox_get_muter(e, ColorRGBs, colorRGBs);
    resize_memory_component(ColorRGBs, colorRGBs, color_rgb, 8)
    for (int i = 0; i < 8; i++) {
        colorRGBs->value[i] = (color_rgb) {155 - (rand() % 60), 225 - (rand() % 60), 255 - (rand() % 60) };
    }
    return e;
}