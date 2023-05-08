void add_chunk(ecs_world_t *world, ecs_entity_t prefab, int3 size) {
    zoxel_add_tag(world, prefab, Chunk);
    zoxel_add(world, prefab, ChunkData);
    zoxel_set(world, prefab, ChunkSize, { size });
    zoxel_set(world, prefab, ChunkDirty, { 0 });
    zoxel_set(world, prefab, ChunkPosition, { { 0, 0, 0 } });
    zoxel_set(world, prefab, VoxLink, { 0 });
}

void add_chunk_colors(ecs_world_t *world, ecs_entity_t prefab) {
    zoxel_add(world, prefab, ColorRGBs);
    if (!headless) {
        zoxel_add(world, prefab, MeshColorRGBs);
    }
}

void add_generate_chunk(ecs_world_t *world, ecs_entity_t e) {
    zoxel_set(world, e, EntityDirty, { 0 });
    zoxel_set(world, e, GenerateChunk, { 1 });
}

void add_noise_chunk(ecs_world_t *world, ecs_entity_t e) {
    zoxel_add_tag(world, e, NoiseChunk);
    zoxel_set(world, e, EntityDirty, { 0 });
    zoxel_set(world, e, GenerateChunk, { 1 });
    // zoxel_set(world, e, AnimateTexture, { 0.0 });
}