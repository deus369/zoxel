ecs_entity_t prefab_character3D = 0;
ecs_entity_t local_character3D = 0;
extern ecs_entity_t healthbar_2D;

int get_characters_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Character3D));
}

ecs_entity_t spawn_prefab_character3D(ecs_world_t *world) {
    zox_prefab_child(prefab_vox)
    zox_prefab_name("prefab_character3D")
    add_seed(world, e, 999);
    add_physics3D(world, e);
    if (!headless) add_gpu_colors(world, e);
    zox_add_tag(e, Character3D)
    zox_prefab_set(e, Dead, { 0 })
    zox_prefab_set(e, DiedTime, { 0 })
    zox_prefab_set(e, AnimationState, { zox_animation_idle })
    zox_prefab_set(e, AnimationStart, { 0 })
    zox_prefab_set(e, Bounds3D, {{ 1, 1, 1 }})
    zox_prefab_set(e, VoxLink, { 0 })
    zox_add_tag(e, LinkChunk)
    zox_prefab_set(e, ChunkLink, { 0 })
    zox_prefab_set(e, ChunkPosition, { int3_chaos })
    zox_prefab_set(e, VoxelPosition, { int3_zero})
    zox_prefab_set(e, ElementLinks, { 0, NULL})
    zox_prefab_set(e, Children, { 0, NULL})         // for bones, particles, etc (transforms)
    prefab_character3D = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawn_prefab character3D [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, const vox_file *vox, float3 position, float4 rotation, unsigned char lod, unsigned char is_player_character) {
    zox_instance(prefab)
    zox_prefab_name("character3D")
    // transforms
    zox_set(e, Position3D, { position })
    zox_set(e, LastPosition3D, { position })
    zox_set(e, Rotation3D, { rotation })
    // voxels
    zox_set(e, VoxLink, { local_terrain })
    set_vox_from_vox_file(world, e, vox);
    /// rendering
    zox_set(e, RenderLod, { lod })
    spawn_gpu_mesh(world, e);
    spawn_gpu_colors(world, e);
    // stats
    float health = (0.02f + 0.98f * ((rand() % 100) * 0.01f)) * 5.0f;
    float max_health = 10.0f;
    int stats_count = 1;
    if (is_player_character) stats_count++;
    // todo: make prefab for health_stat, etc
    UserStatLinks *userStatLinks = zox_get_mut(e, UserStatLinks)
    resize_memory_component(UserStatLinks, userStatLinks, ecs_entity_t, stats_count)
    // health
    ecs_entity_t health_stat = spawn_user_stat(world, e);
    zox_add_tag(health_stat, HealthStat)
    zox_add_tag(health_stat, StateStat)
    zox_prefab_set(health_stat, StatValue, { health })
    zox_prefab_set(health_stat, StatValueMax, { max_health })
    userStatLinks->value[0] = health_stat;
    // soul experience
    if (is_player_character) {
        ecs_entity_t soul_stat = spawn_user_stat(world, e);
        zox_add_tag(soul_stat, LevelStat)
        zox_prefab_set(soul_stat, StatValue, { 1 })
        zox_prefab_set(soul_stat, ExperienceValue, { 0 })
        zox_prefab_set(soul_stat, ExperienceMax, { 10 })
        userStatLinks->value[1] = soul_stat;
    }
    zox_modified(e, UserStatLinks)
    // character ui
#ifndef zox_disable_statbars
    ecs_entity_t statbar = spawn_elementbar3D(world, e, health / max_health);
    zox_prefab_set(statbar, UserStatLink, { health_stat })
    ElementLinks *elementLinks = zox_get_mut(e, ElementLinks)
    resize_memory_component(ElementLinks, elementLinks, ecs_entity_t, 1)
    elementLinks->value[0] = statbar;
    zox_modified(e, ElementLinks)
    if (is_player_character) zox_prefab_set(healthbar_2D, UserStatLink, { health_stat })
#endif
#ifdef zoxel_debug_spawns
    zox_log("   > spawned character3D [%lu]\n", e)
#endif
    return e;
}
