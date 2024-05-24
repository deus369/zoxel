ecs_entity_t prefab_character3D = 0;
ecs_entity_t local_character3D = 0;

int get_characters_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Character3D));
}

ecs_entity_t spawn_prefab_character3D(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_character3D")
    zox_add_tag(e, Character3D)
    // transform
    add_physics3D(world, e);
    zox_prefab_set(e, Bounds3D, { float3_one })
    zox_prefab_set(e, Position3DBounds, { float6_zero })
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
    zox_prefab_set(e, ZoxName, { 0, NULL })
    // stats / death
    zox_prefab_set(e, Dead, { 0 })
    zox_prefab_set(e, DiedTime, { 0 })
    zox_prefab_set(e, StatLinks, { 0, NULL })       // stats
    zox_prefab_set(e, DotLinks, { 0, NULL })        //  - dots
    // more
    zox_prefab_set(e, Children, { 0, NULL})         // for bones, particles, etc (transforms)
    zox_prefab_set(e, ElementLinks, { 0, NULL})     // uis
    zox_prefab_set(e, ItemLinks, { 0, NULL })       // items
    zox_prefab_set(e, SkillLinks, { 0, NULL })      // skills
    zox_prefab_set(e, ActionLinks, { 0, NULL })     // actions
    prefab_character3D = e;
    return e;
}

ecs_entity_2 spawn_character3D(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t vox, const float3 position, const float4 rotation, const unsigned char lod, const ecs_entity_t player, const float vox_scale, const unsigned char render_disabled) {
    zox_instance(prefab)
    zox_name("character3D")
    zox_set(e, RenderDisabled, { render_disabled })
    zox_set(e, Position3D, { position })
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
    // stats
    float health = (0.02f + 0.98f * ((rand() % 100) * 0.01f)) * 5.0f;
    float max_health = 10.0f;
    int stats_count = 1;
    if (player) stats_count++;
    StatLinks *statLinks = zox_get_mut(e, StatLinks)
    resize_memory_component(StatLinks, statLinks, ecs_entity_t, stats_count)
    // health
    const ecs_entity_t health_stat = spawn_user_stat(world, meta_stat_health, e);
    zox_set(health_stat, StatValue, { health })
    zox_set(health_stat, StatValueMax, { max_health })
    statLinks->value[0] = health_stat;
    // soul experience
    if (player) statLinks->value[1] = spawn_user_stat(world, meta_stat_soul, e);
    zox_modified(e, StatLinks)
    // character ui
#ifndef zox_disable_statbars
    const ecs_entity_t statbar = spawn_elementbar3D(world, prefab_statbar3D, e, health / max_health, render_disabled);
    zox_prefab_set(statbar, StatLink, { health_stat })
    ElementLinks *elementLinks = zox_get_mut(e, ElementLinks)
    resize_memory_component(ElementLinks, elementLinks, ecs_entity_t, 1)
    elementLinks->value[0] = statbar;
    zox_modified(e, ElementLinks)
    if (player) {
        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
        find_child_with_tag(canvas, MenuInGame, game_menu)
        if (game_menu) {
            find_child_with_tag(game_menu, ElementBar, healthbar_2D)
            zox_set(healthbar_2D, StatLink, { health_stat })
        }
    }
#endif
    return (ecs_entity_2) { e, health_stat };
}
