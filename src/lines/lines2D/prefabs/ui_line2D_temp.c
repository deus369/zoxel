ecs_entity_t prefab_temporary_ui_line2D;
ecs_entity_t prefab_temporary_line2D;

ecs_entity_t spawn_prefab_ui_line2D_temp(ecs_world_t *world) {
    zox_prefab_child(prefab_ui_line2D)
    // ecs_add_id(world, e, EcsPrefab);
    zox_prefab_name("prefab_ui_line2D_temp")
    zox_prefab_set(e, DestroyInTime, { 0 })
    prefab_temporary_ui_line2D = e;
    return e;
}

ecs_entity_t spawn_prefab_line2D_temp(ecs_world_t *world) {
    zox_prefab_child(prefab_line2D)
    // ecs_add_id(world, e, EcsPrefab);
    zox_prefab_name("prefab_line2D_temp")
    zox_prefab_set(e, DestroyInTime, { 0 })
    prefab_temporary_line2D = e;
    return e;
}
