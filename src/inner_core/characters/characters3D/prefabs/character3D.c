ecs_entity_t spawn_prefab_character3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_character3D")
    zox_add_tag(e, Character3D)
    // transform
    add_physics3D(world, e);
    zox_prefab_set(e, Bounds3D, { (float3) { 0.25f, 0.25f, 0.25f } })
    zox_prefab_set(e, Position3DBounds, { float6_zero })
    zox_prefab_set(e, DisableMovement, { 0 })
    // voxels
    zox_add_tag(e, LinkChunk)
    zox_prefab_set(e, VoxLink, { 0 })
    zox_prefab_set(e, ChunkLink, { 0 })
    zox_prefab_set(e, ChunkPosition, { int3_chaos })
    zox_prefab_set(e, VoxelPosition, { int3_zero})
    // animation
    zox_prefab_set(e, AnimationState, { zox_animation_idle })
    zox_prefab_set(e, AnimationStart, { 0 })
    // generation
    add_seed(world, e, 999);
    // name
    zox_prefab_add(e, ZoxName)
    // more
    zox_prefab_add(e, Children)         // for bones, particles, etc (transforms)
    zox_prefab_add(e, ElementLinks)     // uis
    return e;
}

extern ecs_entity_t spawn_character_stats(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player, const unsigned char render_disabled);
extern void spawn_character_items(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player);
extern void spawn_character_skills(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player);
extern void spawn_character_quests(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player);
extern void spawn_character_actions(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t player);

ecs_entity_2 spawn_character3D(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t vox, const float3 position, const float4 rotation, const unsigned char lod, const ecs_entity_t player, const float vox_scale, const unsigned char render_disabled) {
    zox_instance(prefab)
    zox_name("character3D")
    zox_set(e, RenderDisabled, { render_disabled })
    zox_set(e, Position3D, { position })
    // make a create_bounds function tthat returns float6
    const float min_x_global = -(terrain_spawn_distance) * (real_chunk_scale) + 0.1f;
    const float max_x_global = (terrain_spawn_distance + 1) * (real_chunk_scale) - 0.1f;
    const float min_z_global = min_x_global;
    const float max_z_global = max_x_global;
    const float min_y_global = - real_chunk_scale * terrain_vertical;
    const float max_y_global = - min_y_global + real_chunk_scale;
    if (!player) {
        const int bounds_radius = 16;
        const int bounds_radius_y = 12;
        const float min_x_local = position.x - bounds_radius;
        const float max_x_local = position.x + bounds_radius;
        const float min_z_local = position.z - bounds_radius;
        const float max_z_local = position.z + bounds_radius;
        const float min_y_local = position.y - bounds_radius_y;
        const float max_y_local = position.y + bounds_radius_y;
        zox_set(e, Position3DBounds, {{
            float_max(min_x_local, min_x_global), float_min(max_x_local, max_x_global),
            float_max(min_y_local, min_y_global), float_min(max_y_local, max_y_global),
            float_max(min_z_local, min_z_global), float_min(max_z_local, max_z_global) }})
    } else {
        zox_set(e, Position3DBounds, {{ min_x_global, max_x_global, min_y_global, max_y_global, min_z_global, max_z_global }})
        // zox_set(e, VoxScale, { player_vox_model_scale })
    }
    if (vox_scale) zox_set(e, VoxScale, { vox_scale })
    zox_set(e, LastPosition3D, { position })
    zox_set(e, Rotation3D, { rotation })
    // voxels
    zox_set(e, VoxLink, { local_terrain })
    clone_vox_data(world, e, vox);
    /// rendering
    zox_set(e, RenderLod, { lod })
    spawn_gpu_mesh(world, e);
    spawn_gpu_colors(world, e);
    // name
    char *name = generate_name();
    zox_set(e, ZoxName, { text_to_zext(name) })
    free(name);
    spawn_character_actions(world, e, player);
    spawn_character_items(world, e, player);
    spawn_character_skills(world, e, player);
    spawn_character_quests(world, e, player);
    const ecs_entity_t health = spawn_character_stats(world, e, player, render_disabled);
    return (ecs_entity_2) { e, health };
}
