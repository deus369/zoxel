// data only
ecs_entity_t spawn_prefab_chunk_base(ecs_world_t *world) {
    const byte max_length = 32; // todo: Calculate this from max resolution!
    const int3 size = (int3) { max_length, max_length, max_length };
    zox_prefab()
    zox_prefab_name("chunk_base")
    zox_add_tag(e, Chunk)
    zox_prefab_set(e, ChunkPosition, { int3_zero })
    zox_prefab_set(e, ChunkSize, { size })
    zox_prefab_set(e, VoxLink, { 0 })
    zox_prefab_set(e, ChunkNeighbors, { { 0, 0, 0, 0, 0, 0 } })
    zox_prefab_set(e, RenderLod, { 255 })
    zox_prefab_set(e, RenderDistance, { 255 })
    // states
    // zox_prefab_set(e, ChunkDirty, { chunk_dirty_state_none })
    zox_prefab_set(e, ChunkLodDirty, { 0 }) // chunk_lod_state_spawning })
    zox_prefab_set(e, ChunkMeshDirty, { chunk_dirty_state_none })
    // allocations
    zox_prefab_add(e, VoxelNode)
    zox_prefab_set(e, NodeDepth, { 0 })
    return e;
}