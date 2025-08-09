ecs_entity_t spawn_chunk_terrain(
    ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t terrain,
    const int3 camera_position,
    const int3 position,
    const byte terrain_depth,
    const float scale
) {
    zox_instance(prefab)
    zox_name("chunk_terrain")
    if (terrain_mode == terrain_mode_flatlands) {
        zox_add_tag(e, FlatlandChunk)
    }
    // convert chunk position to real
    //  - scales by length of chunk and vox scale
    zox_set(e, VoxLink, { terrain });
    zox_set(e, ChunkPosition, { position });
    zox_set(e, VoxScale, { scale });    // set from parent

    byte terrain_length = powers_of_two[terrain_depth];
    const float chunk_scale = ((float) terrain_length) * scale;
    const float3 positionf = float3_scale(
        float3_from_int3(position),
        chunk_scale
    );
    zox_set(e, ChunkSize, { int3_single(terrain_length) });
    // zox_log("placing: chunk_scale [%f] voxscale [%f] terrain_length [%i]", chunk_scale, scale, terrain_length);

    zox_set(e, Position3D, { positionf })
    zox_set(e, TransformMatrix, { float4x4_position(positionf) })
    // lod update here
    // todo: just start this as invisible and update with streaming systems
    const byte camera_distance = get_camera_chunk_distance_xz(camera_position, position);
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
