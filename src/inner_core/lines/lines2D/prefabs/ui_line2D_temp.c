ecs_entity_t prefab_temporary_ui_line2D;
ecs_entity_t prefab_temporary_line2D;

ecs_entity_t spawn_prefab_ui_line2D_temp(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_line2D)
    // ecs_add_id(world, e, EcsPrefab);
    zox_prefab_name("prefab_ui_line2D_temp")
    zox_prefab_set(e, DestroyInTime, { 0 })
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab ui_line2D_temp [%lu].\n", (long int) (e));
    #endif
    prefab_temporary_ui_line2D = e;
    return e;
}

ecs_entity_t spawn_prefab_line2D_temp(ecs_world_t *world) {
    zox_prefab_child(prefab_line2D)
    // ecs_add_id(world, e, EcsPrefab);
    zox_prefab_name("prefab_line2D_temp")
    zox_prefab_set(e, DestroyInTime, { 0 })
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab line2D_temp [%lu].\n", (long int) (e));
    #endif
    prefab_temporary_line2D = e;
    return e;
}