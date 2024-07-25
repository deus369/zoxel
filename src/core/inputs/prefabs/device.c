ecs_entity_t spawn_prefab_device(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("device")
    zox_add_tag(e, Device)
    zox_prefab_add(e, Children)
    zox_prefab_add(e, PlayerLink) // used by what player
    return e;
}
