ecs_entity_t prefab_character3D = 0;
ecs_entity_t local_character3D = 0;

int get_characters_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Character3D));
}

ecs_entity_t spawn_prefab_character3D(ecs_world_t *world) {
    zox_prefab_child(prefab_vox)
    zox_prefab_name("prefab_character3D")
    zox_add_tag(e, Character3D)
    add_seed(world, e, 999);
    add_physics3D(world, e);
    zox_set(e, Bounds3D, {{ 1, 1, 1 }})
    zox_add(e, VoxLink)
    zox_set(e, ChunkLink, { 0 })
    zox_set(e, ChunkPosition, { int3_chaos })
    zox_set(e, VoxelPosition, { int3_zero})
    zox_set(e, ElementLinks, { 0, NULL})
    if (!headless) ecs_remove(world, e, MaterialGPULink);
    if (!headless) add_gpu_colors(world, e);
    prefab_character3D = e;
    #ifdef zoxel_debug_prefabs
        zox_log(" > spawn_prefab character3D [%lu].\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, const vox_file *vox, float3 position, float4 rotation, unsigned char lod) {
    zox_instance(prefab)
    // transform
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, LastPosition3D, { position })
    zox_set_only(e, Rotation3D, { rotation })
    // voxels
    zox_set_only(e, VoxLink, { local_terrain })
    set_vox_from_vox_file(world, e, vox);
    // stats
    float health = (0.02f + 0.98f * ((rand() % 100) * 0.01f)) * 5.0f;
    float max_health = 10.0f;
    ecs_entity_t user_stat = spawn_user_stat(world);
    zox_set(user_stat, StatValue, { health })
    zox_set(user_stat, StatValueMax, { max_health })
    UserStatLinks *userStatLinks = ecs_get_mut(world, e, UserStatLinks);
    resize_memory_component(UserStatLinks, userStatLinks, ecs_entity_t, 1)
    userStatLinks->value[0] = user_stat;
    ecs_modified(world, e, UserStatLinks);
    // character ui
    #ifndef zox_disable_statbars
        ecs_entity_t statbar = spawn_statbar3D(world, e, health / max_health);
        zox_set(statbar, UserStatLink, { user_stat })
        ElementLinks *elementLinks = ecs_get_mut(world, e, ElementLinks);
        resize_memory_component(ElementLinks, elementLinks, ecs_entity_t, 1)
        elementLinks->value[0] = statbar;
        ecs_modified(world, e, ElementLinks);
    #endif
    /// rendering
    zox_set_only(e, RenderLod, { lod })
    spawn_gpu_mesh(world, e);
    spawn_gpu_colors(world, e);
    characters_count++;
    #ifdef zoxel_debug_spawns
        zox_log("   > spawned character3D [%lu]\n", e)
    #endif
    return e;
}