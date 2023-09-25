ecs_entity_t prefab_character3D = 0;
ecs_entity_t local_character3D = 0;

int get_characters_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(Character3D));
}

ecs_entity_t spawn_prefab_character3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_vox)
    zox_prefab_name("prefab_character3D")
    zox_add_tag(e, Character3D)
    add_seed(world, e, 999);
    add_physics3D(world, e);
    zox_set(e, Bounds3D, {{ 1, 1, 1 }})
    zox_add(e, VoxLink)
    zox_set(e, ChunkLink, { 0 })
    zox_set(e, ChunkPosition, { int3_zero })
    zox_set(e, VoxelPosition, {{ 0, 0, 0 }})
    zox_set(e, ElementLinks, { 0, NULL})
    if (!headless) ecs_remove(world, e, MaterialGPULink);
    if (!headless) add_gpu_colors(world, e);
    // initialize_new_chunk_octree(world, e, max_octree_depth_character);
    ecs_defer_end(world);
    prefab_character3D = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab character3D [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, const vox_file *vox, float3 position, float4 rotation, unsigned char lod) {
    zox_instance(prefab)
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, LastPosition3D, { position })
    zox_set_only(e, Rotation3D, { rotation })
    zox_set_only(e, VoxLink, { local_terrain })
    zox_set_only(e, RenderLod, { lod })
    float health = (0.02f + 0.98f * ((rand() % 100) * 0.01f)) * 5.0f;
    // spawn health and healthbar
    ecs_entity_t user_stat = spawn_user_stat(world);
    zox_set(user_stat, StatValue, { health })
    zox_set(user_stat, StatValueMax, { 10.0f })
    ecs_entity_t statbar = spawn_statbar3D(world, e);
    zox_set(statbar, UserStatLink, { user_stat })
    UserStatLinks *userStatLinks = ecs_get_mut(world, e, UserStatLinks);
    ElementLinks *elementLinks = ecs_get_mut(world, e, ElementLinks);
    initialize_memory_component(userStatLinks, ecs_entity_t, 1)
    initialize_memory_component(elementLinks, ecs_entity_t, 1)
    userStatLinks->value[0] = user_stat;
    elementLinks->value[0] = statbar;
    ecs_modified(world, e, UserStatLinks);
    ecs_modified(world, e, ElementLinks);
    /// spawn gpu data
    spawn_gpu_mesh(world, e);
    spawn_gpu_colors(world, e);
    set_vox_from_vox_file(world, e, vox);
    characters_count++;
    // zoxel_log(" > character [%lu]\n", e);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned character3D [%lu]\n", (long int) e);
    #endif
    return e;
}