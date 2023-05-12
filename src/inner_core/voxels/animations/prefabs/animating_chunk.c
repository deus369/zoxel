ecs_entity_t prefab_animating_chunk;

ecs_entity_t spawn_prefab_animating_chunk(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_noise_chunk);
    ecs_add_id(world, e, EcsPrefab);
    zoxel_add_tag(e, ColorChunk)
    zoxel_set(world, e, ChunkSize, {{ 16, 16, 16 }});
    zoxel_set(world, e, AnimateChunk, { 1.0 });
    ecs_set(world, e, ChunkDirty, { 0 });
    ecs_set(world, e, MeshDirty, { 0 });
    add_gpu_colors(world, e);
    // set colors
    ColorRGBs *colorRGBs = ecs_get_mut(world, e, ColorRGBs);
    re_initialize_memory_component(colorRGBs, color_rgb, 8);
    for (int i = 0; i < 8; i++)
        colorRGBs->value[i] = (color_rgb) {155 - (rand() % 60), 225 - (rand() % 60), 255 - (rand() % 60) };
    ecs_modified(world, e, ColorRGBs);
    ecs_defer_end(world);
    prefab_animating_chunk = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab animating_chunk [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_animating_chunk(ecs_world_t *world, float3 position, float scale) {
    ecs_entity_t e = spawn_chunk(world, prefab_animating_chunk, position, scale);
    add_chunk_colors(world, e);
    ecs_set(world, e, AnimateChunk, { (((rand() % 100) / 100.0f) * animating_chunk_speed) });
    spawn_gpu_colors(world, e);
    zoxel_log(" > spawned animating_chunk at [%fx%fx%f]\n", position.x, position.y, position.z);
    return e;
}

void test_animating_chunks(ecs_world_t *world, float3 position) {
    const float spawn_scale = 1.0f;
    const float spawnRange = 0.5f; // 16.0f; // 0.96f;
    // float3 position = ecs_get(world, main_cameras[0], Position3D)->value;
    spawn_animating_chunk(world, (float3) { position.x, position.y, position.z + 1 }, spawn_scale * 2.0f);
    // spawn_animating_chunk(world, (float3) { position.x, position.y, position.z - 1 }, spawn_scale * 2.0f);
    // spawn_animating_chunk(world, (float3) { position.x + 1, position.y, position.z }, spawn_scale * 2.0f);
    // spawn_animating_chunk(world, (float3) { position.x - 1, position.y, position.z }, spawn_scale * 2.0f);
    /*spawn_animating_chunk(world, (float3) { 0, 0, -spawnRange }, spawn_scale);
    spawn_animating_chunk(world, (float3) { 0, 0, spawnRange }, spawn_scale);
    spawn_animating_chunk(world, (float3) { -spawnRange, 0, 0 }, spawn_scale);
    spawn_animating_chunk(world, (float3) { spawnRange, 0, 0 }, spawn_scale);*/
}

// extern void generate_chunk_noise(ChunkData* chunkData, const ChunkSize *chunkSize);
/*const ChunkSize *chunkSize = ecs_get(world, e, ChunkSize);
ChunkData *chunkData = ecs_get_mut(world, e, ChunkData);
int voxels_array_size = chunkSize->value.x * chunkSize->value.y * chunkSize->value.z;
re_initialize_memory_component(chunkData, unsigned char, voxels_array_size);
generate_chunk_noise(chunkData, chunkSize);
ecs_modified(world, e, ChunkData);*/