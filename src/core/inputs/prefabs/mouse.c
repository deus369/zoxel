ecs_entity_t spawn_prefab_mouse(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_mouse")
    zox_add_tag(e, Device)
    zox_add_tag(e, Mouse)
    zox_prefab_set(e, MouseLock, { 0 })
    zox_prefab_add(e, Children)
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
    mouse_entity = e;
    return e;
}

unsigned char mouse_is_any_input(ecs_world_t *world, const ecs_entity_t e) {
    if (!e || !ecs_is_alive(world, e)) return 0;
    const Children *children = zox_get(e, Children)
    for (int i = 0; i < children->length; i++) {
        ecs_entity_t e = children->value[i];
        if (!zox_has(e, ZevicePointer)) continue;
        const ZevicePointer *zevicePointer = zox_get(e, ZevicePointer)
        if (zevice_pointer_has_input(zevicePointer)) return 1;
    }
    return 0;
}
