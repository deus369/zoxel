ecs_entity_t prefab_realm;

ecs_entity_t spawn_prefab_realm(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    set_unique_entity_name(world, e, "prefab_realm");
    zox_add_tag(e, Realm);
    zox_set(e, VoxelLinks, { 0, NULL })
    ecs_defer_end(world);
    prefab_realm = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab realm [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t local_realm;

ecs_entity_t spawn_realm(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_instance(prefab_realm)
    set_unique_entity_name(world, e, "realm");
    // spawn voxels
    VoxelLinks voxelLinks = { };
    initialize_memory_component_non_pointer(voxelLinks, ecs_entity_t, 8)
    for (int i = 0; i < 8; i++) {
        ecs_entity_t voxel_entity = spawn_voxel(world);
        voxelLinks.value[i] = voxel_entity;
    }
    zox_set_only(e, VoxelLinks, { voxelLinks.length, voxelLinks.value })
    ecs_defer_end(world);
    local_realm = e;
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned realm [%lu]\n", (long int) e);
    #endif
    return e;
}