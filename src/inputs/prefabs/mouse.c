ecs_entity_t spawn_prefab_mouse(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("mouse")
    zox_add_tag(e, Mouse)
    zox_prefab_set(e, MouseLock, { 0 })
    return e;
}

ecs_entity_t spawn_mouse(ecs_world_t *world) {
    zox_instance(prefab_mouse)
    zox_name("mouse")
    zox_get_muter(e, Children, children)
    const ecs_entity_t pointer = spawn_zevice_pointer(world, e, 0, 0);
    zox_prefab_set(pointer, ZevicePointerRight, { 0 })
    zox_prefab_set(pointer, ZeviceWheel, { int2_zero })
    add_to_Children(children, pointer);
    return e;
}