ecs_entity_t spawn_prefab_temporary_line3D(ecs_world_t *world) {
    zox_prefab_child(prefab_line3D)
    zox_prefab_name("prefab_temporary_line3D")
    zox_prefab_set(e, DestroyInTime, { 0 })
    prefab_temporary_line3D = e;
    return e;
}
