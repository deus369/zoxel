ecs_entity_t spawn_prefab_device_button(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("zevice_button")
    zox_add_tag(e, Zevice)
    zox_prefab_set(e, ZeviceDisabled, { 0 })
    zox_prefab_set(e, ZeviceButton, { 0 })
    zox_prefab_set(e, DeviceButtonType, { 0 })
    zox_prefab_set(e, RealButtonIndex, { 0 })
    return e;
}

ecs_entity_t spawn_device_button(ecs_world_t *world, const byte type, const byte index) {
    zox_instance(prefab_zevice_button)
    zox_name("zevice_button")
    zox_set(e, DeviceButtonType, { type })
    zox_set(e, RealButtonIndex, { index })
    return e;
}
