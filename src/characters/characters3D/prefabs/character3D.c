ecs_entity_t spawn_prefab_character3D(ecs_world_t *world, const ecs_entity_t prefab) {
    if (!prefab) {
        return 0;
    }
    zox_prefab_child(prefab)
    zox_prefab_name("character3D")
    zox_add_tag(e, Character3D)
    // generation
    zox_prefab_set(prefab, Seed, { 999 })
    // name
    zox_prefab_add(e, ZoxName)
    // physics
    add_physics3D(world, e, (float3) { 0.25f, 0.25f, 0.25f });
    // constraints
    zox_prefab_set(e, Position3DBounds, { float6_zero })
    // voxels
    zox_add_tag(e, LinkChunk)
    zox_prefab_set(e, VoxLink, { 0 })
    zox_prefab_set(e, ChunkLink, { 0 })
    zox_prefab_set(e, ChunkPosition, { int3_chaos })
    zox_prefab_set(e, VoxelPosition, { int3_zero })
    // Vox
    zox_prefab_set(e, CloneVox, { 0 })
    zox_prefab_set(e, CloneVoxLink, { 0 })
    zox_prefab_set(e, ChunkLod, { 255 })
    // animation
    zox_prefab_set(e, AnimationState, { zox_animation_idle })
    zox_prefab_set(e, AnimationStart, { 0 })
    // hierarchy
    zox_prefab_add(e, Children)         // for bones, particles, etc (transforms)
    zox_prefab_add(e, ElementLinks)     // uis
    return e;
}

ecs_entity_t spawn_character3D(ecs_world_t *world, const spawn_character3D_data data) {
    zox_instance(data.prefab)
    zox_name("character3D")
    // make a create_bounds function tthat returns float6
    const float min_x_global = -(terrain_spawn_distance) * (real_chunk_scale) + 0.1f;
    const float max_x_global = (terrain_spawn_distance + 1) * (real_chunk_scale) - 0.1f;
    const float min_z_global = min_x_global;
    const float max_z_global = max_x_global;
    const float min_y_global = - real_chunk_scale * terrain_vertical;
    const float max_y_global = - min_y_global + real_chunk_scale;
    float6 character_bounds = (float6) { min_x_global, max_x_global, min_y_global, max_y_global, min_z_global, max_z_global };
    if (!data.player) {
        const int bounds_radius = 16;
        const int bounds_radius_y = 12;

        const float min_x_local = data.position.x - bounds_radius;
        const float max_x_local = data.position.x + bounds_radius;

        const float min_y_local = data.position.y - bounds_radius_y;
        const float max_y_local = data.position.y + bounds_radius_y;

        const float min_z_local = data.position.z - bounds_radius;
        const float max_z_local = data.position.z + bounds_radius;
        character_bounds = (float6) {
            min_x_local, max_x_local,
            min_y_local, max_y_local,
            min_z_local, max_z_local };
        zox_set(e, Position3DBounds, { character_bounds })
    }
    // disabled bounds for now
    zox_set(e, RenderDisabled, { data.render_disabled })
    zox_set(e, Position3D, { data.position })
    zox_set(e, LastPosition3D, { data.position })
    zox_set(e, Rotation3D, { data.rotation })
    // voxels
    if (data.terrain) {
        zox_set(e, VoxLink, { data.terrain })
    }
    if (data.terrain_chunk) {
        // zox_log("[spawn_character3D] setting character [%lu] chunk: %lu", e, data.terrain_chunk)
        zox_set(e, ChunkLink, { data.terrain_chunk })
    }
    if (data.scale) {
        zox_set(e, VoxScale, { data.scale })
    }
    zox_set(e, CloneVoxLink, { data.vox })
    zox_set(e, CloneVox, { 1 })
    // name
    char *name = generate_name();
    zox_set(e, ZoxName, { text_to_zext(name) })
    // user hooks
    spawned_character3D_data spawned_data = (spawned_character3D_data) {
        .e = e,
        .p = data.player,
        .name = name,
        .render_disabled = data.render_disabled,
        .elementLinks = &((ElementLinks) { 0, NULL }),
    };
    run_hook_spawned_character3D(world, &spawned_data);
    // done!
    zox_set(e, ElementLinks, { spawned_data.elementLinks->length, spawned_data.elementLinks->value })
    free(name);
    /// rendering
    zox_set(e, RenderLod, { data.lod })
    spawn_gpu_mesh(world, e);
    spawn_gpu_colors(world, e);
    return e;
}