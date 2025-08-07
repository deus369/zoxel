entity spawn_prefab_element3D_invisible(ecs *world) {
    zox_prefab()
    zox_prefab_name("element3D_invisible")
    zox_add_tag(e, Element3D)
    add_element3D_transform(world, e);
    add_element3D_child(world, e);
    return e;
}
