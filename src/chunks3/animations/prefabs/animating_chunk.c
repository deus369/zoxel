ecs_entity_t spawn_prefab_animating_chunk(
    ecs_world_t *world,
    const ecs_entity_t prefab
) {
    const int3 chunk_size = int3_single(16);
    zox_instance(prefab);
    zox_make_prefab(e);
    // ecs_add_id(world, e, EcsPrefab);
    // prefab_add_chunk_colors(world, e);
    zox_prefab_set(e, ChunkSize, { chunk_size });
    zox_prefab_set(e, AnimateChunk, { 1.0 });
    zox_prefab_set(e, ChunkDirty, { chunk_dirty_state_none });
    zox_prefab_set(e, ChunkMeshDirty, { chunk_dirty_state_none });
    zox_prefab_set(e, MeshDirty, { 0 });
    // testing: set colors
    ColorRGBs colors = (ColorRGBs) { };
    initialize_ColorRGBs(&colors, 8);
    for (int i = 0; i < 8; i++) {
        colors.value[i] = (color_rgb) {
            155 - (rand() % 60),
            225 - (rand() % 60),
            255 - (rand() % 60) };
    }
    zox_set_ptr(e, ColorRGBs, colors);
    if (!headless) {
        add_gpu_colors(world, e);
    }
    return e;
}