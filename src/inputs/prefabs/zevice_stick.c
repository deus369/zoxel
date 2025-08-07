entity spawn_prefab_device_stick(ecs *world) {
    zox_prefab()
    zox_prefab_name("zevice_stick")
    zox_add_tag(e, Zevice)
    zox_prefab_set(e, ZeviceDisabled, { 0 })
    zox_prefab_set(e, ZeviceStick, { float2_zero })
    zox_prefab_set(e, DeviceButtonType, { 0 })
    zox_prefab_set(e, RealButtonIndex, { 0 })
    zox_prefab_set(e, DeviceLink, { 0 })
    return e;
}

entity spawn_zevice_stick(ecs *world, const entity device, const byte type, const byte index) {
    zox_instance(prefab_zevice_stick)
    zox_name("zevice_stick")
    zox_set(e, DeviceLink, { device })
    zox_set(e, DeviceButtonType, { type })
    zox_set(e, RealButtonIndex, { index })
    return e;
}
