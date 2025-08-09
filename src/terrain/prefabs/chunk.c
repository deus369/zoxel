ecs_entity_t spawn_prefab_chunk_terrain(
    ecs_world_t *world,
    const ecs_entity_t prefab,
    const int3 size
) {
    zox_prefab_child(prefab);
    add_components_mesh_textured(world, e);
    // Terrain / Generation
    zox_add_tag(e, StreamedChunk);
    zox_add_tag(e, TerrainChunk);
    zox_add_tag(e, ChunkTextured);
    zox_prefab_set(e, Seed, { 666 });
    zox_prefab_set(e, ChunkLodDirty, { 0 });
    zox_prefab_set(e, GenerateChunk, { 0 });
    zox_prefab_set(e, ChunkEntities, { 0, NULL });
    zox_prefab_set(e, BlocksSpawned, { 0 });
    zox_prefab_set(e, ChunkNeighbors, { { 0, 0, 0, 0, 0, 0 } });
    zox_add_tag(e, ChunkDebugger);
    zox_set(e, RenderDisabled, { 1 });
    // Debug
    zox_prefab_set(e, Bounds3D, { float3_single(1) });  // todo: build this in spawn function
    prefab_add_cube_lines_shrink(world, e, color_white, 0, 0.95f);
    return e;
}