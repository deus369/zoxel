#define zox_device_stick_left 0
#define zox_device_stick_right 1

ecs_entity_t prefab_device_stick;

ecs_entity_t spawn_prefab_device_stick(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_device_stick")
    zox_add_tag(e, Zevice)
    zox_prefab_set(e, ZeviceDisabled, { 0 })
    zox_prefab_set(e, ZeviceStick, { float2_zero })
    zox_prefab_set(e, DeviceButtonType, { 0 })
    zox_prefab_set(e, RealButtonIndex, { 0 })
    prefab_device_stick = e;
    return e;
}

ecs_entity_t spawn_zevice_stick(ecs_world_t *world, const unsigned char type, const unsigned char index) {
    zox_instance(prefab_device_stick)
    zox_name("device_stick")
    zox_prefab_set(e, DeviceButtonType, { type })
    zox_prefab_set(e, RealButtonIndex, { index })
    return e;
}
