ecs_entity_t spawn_prefab_taskbar(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("taskbar")
    zox_add_tag(e, Taskbar)
    zox_prefab_set(e, Children, { 0, NULL });
    return e;
}
