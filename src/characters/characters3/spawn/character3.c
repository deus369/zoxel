ecs_entity_t spawn_character3(ecs_world_t *world,
    const spawn_character3D_data data)
{
    zox_instance(data.prefab)
    zox_name("character3")
    zox_set(e, Position3D, { data.position })
    zox_set(e, LastPosition3D, { data.position })
    if (!float4_equals(data.rotation, quaternion_identity)) {
        zox_set(e, Rotation3D, { data.rotation })
    }
    if (!float3_equals(data.euler, float3_zero)) {
        zox_set(e, Euler, { data.euler })
    }
    // rendering
    if (!data.lod) {
        zox_set(e, RenderLod, { data.lod })
    }
    if (!data.render_disabled) {
        zox_set(e, RenderDisabled, { data.render_disabled })
    }
    if (data.scale) {
        zox_set(e, VoxScale, { data.scale })
    }
    // voxels
    if (data.terrain) {
        zox_set(e, VoxLink, { data.terrain })
    }
    if (data.terrain_chunk) {
        zox_set(e, ChunkLink, { data.terrain_chunk })
        zox_set(e, ChunkPosition, { data.chunk_position })
    }
    if (zox_has(data.prefab, InstanceLink)) {
        zox_set(e, InstanceLink, { data.vox })
        zox_set(e, VoxScale, { vox_model_scale })
    } else {
        zox_set(e, CloneVoxLink, { data.vox })
        zox_set(e, CloneVox, { 1 })
        // move this to new system
        spawn_gpu_mesh(world, e);
        spawn_gpu_colors(world, e);
    }
    // name
    if (!disable_npc_hooks) {
        char *name = generate_name();
        zox_set(e, ZoxName, { text_to_zext(name) })
        spawned_character3D_data spawned_data = (spawned_character3D_data) {
            .realm = zox_gett_value(data.terrain, RealmLink),
            .e = e,
            .p = data.player,
            .name = name,
            .render_disabled = data.render_disabled,
            .elementLinks = &((ElementLinks) { 0, NULL }),
        };
        run_hook_spawned_character3D(world, &spawned_data);
        zox_set(e, ElementLinks, { spawned_data.elementLinks->length, spawned_data.elementLinks->value })
        free(name);
    }

    // make a create_bounds function tthat returns float6
    /*const float min_x_global = -(terrain_spawn_distance) * (real_chunk_scale) + 0.1f;
    const float max_x_global = (terrain_spawn_distance + 1) * (real_chunk_scale) - 0.1f;
    const float min_z_global = min_x_global;
    const float max_z_global = max_x_global;
    const float min_y_global = - real_chunk_scale * terrain_vertical;
    const float max_y_global = - min_y_global + real_chunk_scale;
    float6 character_bounds = (float6) {
        min_x_global,
        max_x_global,
        min_y_global,
        max_y_global,
        min_z_global,
        max_z_global };
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
    }*/
    zox_stats_characters++;
    return e;
}