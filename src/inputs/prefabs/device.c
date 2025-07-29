ecs_entity_t spawn_prefab_device(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("device")
    zox_add_tag(e, Device)
    zox_prefab_set(e, Children, { 0, NULL })
    zox_prefab_set(e, DeviceDisabled, { 1 })
    // zox_prefab_set(e, PlayerLink, { 0 }) // used by what player
    return e;
}