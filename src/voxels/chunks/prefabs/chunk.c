void add_chunk_octree(ecs_world_t *world, const ecs_entity_t e, const int3 size) {
    zox_add_tag(e, Chunk)
    zox_prefab_set(e, ChunkSize, { size })
    zox_prefab_set(e, ChunkDirty, { chunk_dirty_state_none })
    zox_prefab_set(e, ChunkMeshDirty, { chunk_dirty_state_none })
    zox_prefab_set(e, ChunkPosition, { int3_zero })
    zox_prefab_set(e, RenderLod, { 255 })
    zox_prefab_set(e, RenderDistance, { 255 })
    zox_prefab_set(e, ChunkLodDirty, { 0 }) // chunk_lod_state_spawning })
    zox_prefab_set(e, VoxLink, { 0 })
    zox_prefab_add(e, ChunkOctree)
    zox_prefab_add(e, ChunkNeighbors)
    zox_get_muter(e, ChunkNeighbors, chunkNeighbors)
    resize_memory_component(ChunkNeighbors, chunkNeighbors, ecs_entity_t, 6)
    for (byte i = 0; i < 6; i++) chunkNeighbors->value[i] = 0;
}

ecs_entity_t spawn_prefab_chunk(ecs_world_t *world) {
    zox_prefab()
    // Voxels
    // todo: calculate this based on max LOD resolution (2 to power of resolution)
    const byte max_length = 32; // todo: Calculate this from max resolution!
    const int3 size = (int3) { max_length, max_length, max_length };
    add_chunk_octree(world, e, size);
    zox_prefab_set(e, VoxScale, { default_vox_scale })
    // Transforms
    add_transform3Ds(world, e, 0);
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    // Rendering
    zox_prefab_set(e, Brightness, { 1.0f })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, MeshDirty, { 0 })
    prefab_add_mesh_basic(world, e);
    return e;
}