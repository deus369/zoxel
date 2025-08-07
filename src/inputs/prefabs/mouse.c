entity spawn_prefab_mouse(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("mouse")
    zox_add_tag(e, Mouse)
    zox_prefab_set(e, MouseLock, { 0 })
    return e;
}

entity spawn_mouse(ecs *world) {
    zox_instance(prefab_mouse)
    zox_name("mouse")
    zox_get_muter(e, Children, children)
    const entity pointer = spawn_zevice_pointer(world, e, 0, 0);
    zox_prefab_set(pointer, ZevicePointerRight, { 0 })
    zox_prefab_set(pointer, ZeviceWheel, { int2_zero })
    add_to_Children(children, pointer);
    return e;
}