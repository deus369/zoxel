ecs_entity_t spawn_prefab_label(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("label")
    zox_add_tag(e, Label)
    return e;
}