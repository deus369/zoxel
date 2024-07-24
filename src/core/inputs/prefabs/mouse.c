ecs_entity_t spawn_prefab_mouse(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_mouse")
    zox_add_tag(e, Device)
    zox_prefab_set(e, Mouse, mouse_zero)
    zox_prefab_set(e, MouseLock, { 0 })
    return e;
}

ecs_entity_t spawn_mouse(ecs_world_t *world) {
    zox_instance(prefab_mouse)
    zox_name("mouse")
    mouse_entity = e;
    return e;
}
