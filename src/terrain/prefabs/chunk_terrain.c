ecs_entity_t spawn_prefab_terrain_chunk(ecs_world_t *world, const ecs_entity_t prefab, const int3 size) {
    zox_prefab_child(prefab)
    add_components_mesh_textured(world, e);
    // Terrain / Generation
    zox_add_tag(e, StreamedChunk)
    zox_add_tag(e, TerrainChunk)
    zox_add_tag(e, ChunkTextured)
    add_seed(world, e, 666);
    zox_prefab_set(e, ChunkLodDirty, { 0 })
    zox_prefab_set(e, GenerateChunk, { 0 }) // fails on samsung phone?
    // links to sub chunk things - remember: these have to be set to NULL as not set in initialization
    zox_prefab_set(e, EntityLinks, { 0, NULL })
    // zox_prefab_set(e, EntityLinks, { 1, malloc(sizeof(ecs_entity_t)) })
    zox_prefab_set(e, BlocksSpawned, { 0 })
#ifdef zox_disable_frustum_culling
    zox_set(e, RenderDisabled, { 0 })
#else
    zox_set(e, RenderDisabled, { 1 })
#endif
    zox_add_tag(e, ChunkDebugger)
    // neighbors
    // zox_get_muter(e, ChunkNeighbors, chunkNeighbors)
    ChunkNeighbors *chunkNeighbors = &((ChunkNeighbors) { 0, NULL });
    resize_memory_component(ChunkNeighbors, chunkNeighbors, ecs_entity_t, 6)
    for (int i = 0; i < 6; i++) chunkNeighbors->value[i] = 0;
    zox_prefab_set(e, ChunkNeighbors, { chunkNeighbors->length, chunkNeighbors->value })
    return e;
}

ecs_entity_t spawn_chunk_terrain(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t terrain, const int3 camera_position, const int3 chunk_position, const float real_chunk_scale) {
    zox_instance(prefab)
    zox_name("chunk_terrain")
    if (terrain_mode == terrain_mode_flatlands) {
        zox_add_tag(e, FlatlandChunk)
    } else {
        #ifdef zox_is_flatlands
            zox_add_tag(e, FlatlandChunk)
        #endif
    }
    zox_set(e, ChunkOctree, { .max_depth = terrain_depth })
    // zox_get_muter(e, ChunkNeighbors, chunkNeighbors)
    // zox_log("New chunk neighbors: %i\n", chunkNeighbors->length)
    const float3 position3D = float3_multiply_float(float3_from_int3(chunk_position), real_chunk_scale);
    zox_set(e, Position3D, { position3D })
    zox_set(e, VoxLink, { terrain })
    zox_set(e, ChunkPosition, { chunk_position })
    zox_set(e, TransformMatrix, { float4x4_position(position3D) })
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_uvs(world, e);
        spawn_gpu_colors(world, e);
    }
    // neighbors
    ChunkNeighbors *chunkNeighbors = &((ChunkNeighbors) { 0, NULL });
    // zox_get_muter(e, ChunkNeighbors, chunkNeighbors)
    resize_memory_component(ChunkNeighbors, chunkNeighbors, ecs_entity_t, 6)
    for (byte i = 0; i < 6; i++) {
        chunkNeighbors->value[i] = 0;
    }
    zox_set(e, ChunkNeighbors, { chunkNeighbors->length, chunkNeighbors->value })

    // lod update here
    // todo: just start this as invisible and update with streaming systems
    const byte camera_distance = get_camera_chunk_distance(camera_position, chunk_position);
    zox_set(e, RenderDistance, { camera_distance })
    const byte max_camera_distance = render_distance + 1;
    const byte render_lod = get_terrain_lod_from_camera_distance(camera_distance, max_camera_distance, terrain_depth);
    zox_set(e, RenderLod, { render_lod })
    if (render_lod != render_lod_invisible) {
        zox_set(e, ChunkLodDirty, { chunk_lod_state_trigger })
    }
    return e;
}
