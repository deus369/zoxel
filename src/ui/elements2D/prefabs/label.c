entity spawn_prefab_label(ecs *world, const entity prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("label")
    zox_add_tag(e, Label)
    return e;
}