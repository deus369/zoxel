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
    zox_prefab_set(e, EntityLinks, { 0, NULL });
    zox_prefab_set(e, BlocksSpawned, { 0 });
    zox_prefab_set(e, ChunkNeighbors, { { 0, 0, 0, 0, 0, 0 } });
    zox_add_tag(e, ChunkDebugger);
    zox_set(e, RenderDisabled, { 1 });
    return e;
}

ecs_entity_t spawn_chunk_terrain(
    ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t terrain,
    const int3 camera_position,
    const int3 chunk_position,
    const float real_chunk_scale
) {
    zox_instance(prefab)
    zox_name("chunk_terrain")
    if (terrain_mode == terrain_mode_flatlands) {
        zox_add_tag(e, FlatlandChunk)
    }
    const float3 position3D = float3_scale(float3_from_int3(chunk_position), real_chunk_scale);
    zox_set(e, Position3D, { position3D })
    zox_set(e, VoxLink, { terrain })
    zox_set(e, ChunkPosition, { chunk_position })
    zox_set(e, TransformMatrix, { float4x4_position(position3D) })
    // lod update here
    // todo: just start this as invisible and update with streaming systems
    const byte camera_distance = get_camera_chunk_distance_xz(camera_position, chunk_position);
    zox_set(e, RenderDistance, { camera_distance })
    zox_set(e, RenderDistanceDirty, { zox_dirty_trigger })
    // const byte max_camera_distance = render_distance + 1;
    const byte render_lod = distance_to_terrain_lod(camera_distance);
    zox_set(e, RenderLod, { render_lod })
    if (render_lod != render_lod_invisible) {
        zox_set(e, ChunkLodDirty, { chunk_lod_state_trigger })
    }
    // can move this to init systems
    //  note: keep spawn functions only for passing through sending outside information
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_uvs(world, e);
        spawn_gpu_colors(world, e);
    }
    return e;
}
